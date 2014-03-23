/*!
\file GUIProgressControl.h
\brief
*/

#ifndef GUILIB_GUIMARKERCONTROL_H
#define GUILIB_GUIMARKERCONTROL_H

#pragma once

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

#include "GUITexture.h"
#include "GUIControl.h"

#include "boost/shared_ptr.hpp"

/*!
 \ingroup controls
 \brief
 */
class CGUIMarkerControl : public CGUIControl
{
public:
  CGUIMarkerControl(int parentID, int controlID, float posX, float posY,
                    float width, float height,
                    const CTextureInfo& chapterMarkerTexture,
                    const CTextureInfo& edlMarkerTexture,
                    const CTextureInfo& timeshiftMarkerTexture);
  virtual ~CGUIMarkerControl();
  virtual CGUIMarkerControl *Clone() const { return new CGUIMarkerControl(*this); }

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual bool CanFocus() const;
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  virtual bool OnMessage(CGUIMessage& message);
  virtual void SetPosition(float posX, float posY);

protected:
  virtual bool UpdateColors();

private:
  void InitMarkers();

  CTextureInfo m_chapterMarkerTexture;
  CTextureInfo m_edlMarkerTexture;
  CGUITexture  m_guiTimeshiftMarker;
  std::vector<boost::shared_ptr<CGUITexture> > m_guiMarkers;
};

#endif
