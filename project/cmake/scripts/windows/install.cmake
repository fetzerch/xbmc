install(TARGETS ${APP_NAME_LC} DESTINATION ${bindir})

install(FILES ${CORE_SOURCE_DIR}/LICENSE.GPL
              ${CORE_SOURCE_DIR}/copying.txt DESTINATION ${datarootdir})

install(DIRECTORY ${CORE_SOURCE_DIR}/media DESTINATION ${datarootdir})

foreach(file ${install_data})
  get_filename_component(dir ${file} PATH)
  install(FILES ${CMAKE_BINARY_DIR}/${file}
          DESTINATION ${datarootdir}/${dir})
endforeach()

foreach(texture ${XBT_FILES})
  file(RELATIVE_PATH rel ${CMAKE_BINARY_DIR} ${texture})
  get_filename_component(dir ${rel} PATH)
  install(FILES ${texture}
          DESTINATION ${datarootdir}/${dir})
endforeach()

#set(CPACK_GENERATOR NSIS)
#set(CPACK_PACKAGE_NAME ${APP_NAME})
#set(CPACK_PACKAGE_VENDOR ${APP_COMPANY_NAME})
#set(CPACK_PACKAGE_VERSION_MAJOR ${APP_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${APP_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${APP_VERSION_TAG})
set(CPACK_RESOURCE_FILE_LICENSE ${CORE_SOURCE_DIR}/LICENSE.GPL)

set(CPACK_NSIS_MUI_ICON "${CORE_SOURCE_DIR}\\\\tools\\\\windows\\\\packaging\\\\media\\\\application.ico")
set(CPACK_NSIS_MUI_UNICON ${CPACK_NSIS_MUI_ICON})
set(CPACK_NSIS_MUI_HEADERIMAGE_BITMAP "${CORE_SOURCE_DIR}\\\\tools\\\\windows\\\\packaging\\\\media\\\\installer\\\\header.bmp")
set(CPACK_NSIS_MUI_HEADERIMAGE_UNBITMAP ${CPACK_NSIS_MUI_HEADERIMAGE_BITMAP})
set(CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP "${CORE_SOURCE_DIR}\\\\tools\\\\windows\\\\packaging\\\\media\\\\installer\\\\welcome-left.bmp")
set(CPACK_NSIS_MUI_UNWELCOMEFINISHPAGE_BITMAP ${CPACK_NSIS_MUI_WELCOMEFINISHPAGE_BITMAP})

set(CPACK_NSIS_MUI_FINISHPAGE_LINK "Please visit ${WEBSITE} for more information.")
set(CPACK_NSIS_MUI_FINISHPAGE_LINK_LOCATION ${WEBSITE})
set(CPACK_NSIS_MUI_FINISHPAGE_RUN "$INSTDIR\${APP_NAME}.exe")

include (CPack)
