/*
 *      Copyright (C) 2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include "GUIMarkerControl.h"
#include "GUIInfoManager.h"
#include "cores/IPlayer.h"
#include "Application.h"
#include "boost/make_shared.hpp"
#include "utils/MathUtils.h"

#include "pvr/PVRManager.h"
#include "pvr/addons/PVRClients.h"
#include "epg/Epg.h"

CGUIMarkerControl::CGUIMarkerControl(int parentID, int controlID,
                                     float posX, float posY, float width,
                                     float height,
                                     const CTextureInfo& chapterMarkerTexture,
                                     const CTextureInfo& edlMarkerTexture,
                                     const CTextureInfo& timeshiftMarkerTexture)
    : CGUIControl(parentID, controlID, posX, posY, width, height),
      m_chapterMarkerTexture(chapterMarkerTexture),
      m_edlMarkerTexture(edlMarkerTexture),
      m_guiTimeshiftMarker(posX, posY, width, height, timeshiftMarkerTexture)
{
  ControlType = GUICONTROL_MARKER;
  m_guiTimeshiftMarker.SetVisible(false);
}

CGUIMarkerControl::~CGUIMarkerControl()
{
}

void CGUIMarkerControl::InitMarkers()
{
  float reference = m_width / g_application.m_pPlayer->GetTotalTime();

  // Initialize static markers that won't change unless a different video is played (chapters, edl)
  std::vector<SMarkerInfo> markers = g_application.m_pPlayer->GetMarkers();
  for (std::vector<SMarkerInfo>::iterator markerIt = markers.begin(); markerIt != markers.end(); ++markerIt)
  {
    int markerStart = MathUtils::round_int((*markerIt).start * reference);
    switch ((*markerIt).type)
    {
      case IP_MT_CHAPTER:
        // Skip chapter markers positioned at the start
        if (markerStart == 0)
          continue;

        m_guiMarkers.push_back(boost::make_shared<CGUITexture>(m_posX + markerStart, m_posY, 0, 0, m_chapterMarkerTexture));
        break;
      case IP_MT_EDL_COMM_BREAK:
      {
        int markerEnd = MathUtils::round_int((*markerIt).end * reference);
        m_guiMarkers.push_back(boost::make_shared<CGUITexture>(m_posX + markerStart, m_posY, markerEnd-markerStart, 0, m_edlMarkerTexture));
        break;
      }
      default:
        break;
    }
  }
}

void CGUIMarkerControl::SetPosition(float posX, float posY)
{
  CGUIControl::SetPosition(posX, posY);
}

void CGUIMarkerControl::Process(unsigned int currentTime, CDirtyRegionList &dirtyregions)
{
  bool changed = false;

  // Calculate position and width for timeshift marker
  EPG::CEpgInfoTag epgTag;
  if (PVR::g_PVRManager.GetPlayingEpgTag(epgTag))
  {
    time_t epgStart;
    epgTag.StartAsUTC().GetAsTime(epgStart);
    time_t epgEnd;
    epgTag.EndAsUTC().GetAsTime(epgEnd);

    float reference = (epgEnd - epgStart) / m_width;
    int xPos = MathUtils::round_int((float)(PVR::g_PVRClients->GetBufferTimeStart() - epgStart) / reference);
    int yOffset = MathUtils::round_int((float)(m_height - m_guiTimeshiftMarker.GetTextureHeight()) * 0.5f);
    m_guiTimeshiftMarker.SetPosition(m_posX + xPos, m_posY + yOffset);

    int width = MathUtils::round_int((float)(PVR::g_PVRClients->GetBufferTimeEnd() - PVR::g_PVRClients->GetBufferTimeStart()) / reference);
    m_guiTimeshiftMarker.SetWidth(width);
    m_guiTimeshiftMarker.SetHeight(m_guiTimeshiftMarker.GetTextureHeight());
    m_guiTimeshiftMarker.SetVisible(true);
    changed = true;
  } else {
    m_guiTimeshiftMarker.SetVisible(false);
  }

  std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
  while (markerIt != m_guiMarkers.end())
  {
    // Reposition the EDL markers (y-Offset) since their size is now known
    // TODO: Calculate only once
    if ((*markerIt)->GetFileName() == m_edlMarkerTexture.filename)
    {
      int yOffset = (float)(m_height - (*markerIt)->GetTextureHeight()) * 0.5f;
      (*markerIt)->SetPosition((*markerIt)->GetXPosition(), m_posY + yOffset);
    }
    changed |= (*markerIt++)->Process(currentTime);
  }

  if (changed)
    MarkDirtyRegion();

  CGUIControl::Process(currentTime, dirtyregions);
}

void CGUIMarkerControl::Render()
{
  if (!IsDisabled())
  {
    std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
    while (markerIt != m_guiMarkers.end())
      (*markerIt++)->Render();

    m_guiTimeshiftMarker.Render();
  }

  CGUIControl::Render();
}

bool CGUIMarkerControl::CanFocus() const
{
  return false;
}

bool CGUIMarkerControl::OnMessage(CGUIMessage& message)
{
  return CGUIControl::OnMessage(message);
}

void CGUIMarkerControl::FreeResources(bool immediately)
{
  CGUIControl::FreeResources(immediately);

  std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
  while (markerIt != m_guiMarkers.end())
    (*markerIt++)->FreeResources(immediately);
  m_guiMarkers.clear();

  m_guiTimeshiftMarker.FreeResources(immediately);
}

void CGUIMarkerControl::DynamicResourceAlloc(bool bOnOff)
{
  CGUIControl::DynamicResourceAlloc(bOnOff);

  std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
  while (markerIt != m_guiMarkers.end())
    (*markerIt++)->DynamicResourceAlloc(bOnOff);

  m_guiTimeshiftMarker.DynamicResourceAlloc(bOnOff);
}

void CGUIMarkerControl::AllocResources()
{
  CGUIControl::AllocResources();

  InitMarkers();

  std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
  while (markerIt != m_guiMarkers.end())
    (*markerIt++)->AllocResources();

  m_guiTimeshiftMarker.AllocResources();
}

void CGUIMarkerControl::SetInvalid()
{
  CGUIControl::SetInvalid();

  std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
  while (markerIt != m_guiMarkers.end())
    (*markerIt++)->SetInvalid();

  m_guiTimeshiftMarker.SetInvalid();
}

bool CGUIMarkerControl::UpdateColors()
{
  bool changed = CGUIControl::UpdateColors();

  std::vector<boost::shared_ptr<CGUITexture> >::iterator markerIt = m_guiMarkers.begin();
  while (markerIt != m_guiMarkers.end())
      changed |= (*markerIt++)->SetDiffuseColor(m_diffuseColor);

  changed |= m_guiTimeshiftMarker.SetDiffuseColor(m_diffuseColor);

  return changed;
}
