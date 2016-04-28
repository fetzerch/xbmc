# OSX packaging

#set(PACKAGE_OUTPUT_DIR ${CORE_SOURCE_DIR}/build/${CORE_BUILD_CONFIG})

#add_custom_target(osx_copyrootfiles
#    COMMAND "ACTION=build"
#            "TARGET_BUILD_DIR=${PACKAGE_OUTPUT_DIR}"
#            "TARGET_NAME=${APP_NAME}.app"
#            "APP_NAME=${APP_NAME}"
#            "SRCROOT=${CMAKE_BINARY_DIR}"
#            ${CORE_SOURCE_DIR}/tools/darwin/Support/CopyRootFiles-osx.command)

#configure_file(${CORE_SOURCE_DIR}/xbmc/platform/darwin/osx/Info.plist.in
#               ${CMAKE_BINARY_DIR}/xbmc/platform/darwin/osx/Info.plist @ONLY)
#execute_process(COMMAND perl -p -i -e "s/r####/${APP_SCMID}/" ${CMAKE_BINARY_DIR}/xbmc/platform/darwin/osx/Info.plist)
#add_custom_target(osx_copyframeworks
#    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${APP_NAME_LC}> ${PACKAGE_OUTPUT_DIR}/${APP_NAME}
#    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CORE_BUILD_DIR}/DllPaths_generated.h
#                                     ${CMAKE_BINARY_DIR}/xbmc/DllPaths_generated.h
#    COMMAND "XBMC_DEPENDS=${DEPENDS_PATH}"
#            "TARGET_BUILD_DIR=${PACKAGE_OUTPUT_DIR}"
#            "TARGET_NAME=${APP_NAME}.app"
#            "APP_NAME=${APP_NAME}"
#            "FULL_PRODUCT_NAME=${APP_NAME}.app"
#            "SRCROOT=${CMAKE_BINARY_DIR}"
#            ${CORE_SOURCE_DIR}/tools/darwin/Support/copyframeworks-osx.command)
#add_dependencies(osx_copyframeworks osx_copyrootfiles)

## Usually executed from CI (packaging script). Hardcodes path for in source builds.
## Builds dmg into same directory in source tree.
#configure_file(${CORE_SOURCE_DIR}/tools/darwin/packaging/osx/mkdmg-osx.sh.in
#               ${CORE_SOURCE_DIR}/tools/darwin/packaging/osx/mkdmg-osx.sh @ONLY)
#add_custom_target(osx_makedmg
#    COMMAND "SUDO=/usr/bin/sudo" sh ./mkdmg-osx.sh ${CORE_BUILD_CONFIG}
#    WORKING_DIRECTORY ${CORE_SOURCE_DIR}/tools/darwin/packaging/osx)
#add_dependencies(osx_makedmg osx_copyframeworks)

configure_file(${CORE_SOURCE_DIR}/xbmc/platform/darwin/osx/Info.plist.in Info.plist @ONLY)
execute_process(COMMAND perl -p -i -e "s/r####/${APP_SCMID}/" ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)

add_custom_command(TARGET ${APP_NAME_LC} POST_BUILD
                   COMMAND iconutil -c icns -o kodi.icns ${CORE_SOURCE_DIR}/tools/darwin/packaging/media/osx/icon.iconset
                   COMMAND iconutil -c icns -o VolumeIcon.icns ${CORE_SOURCE_DIR}/tools/darwin/packaging/media/osx/volumeIcon.iconset)
#install(FILES kodi.icns VolumeIcon.icns DESTINATION ${TARGET}.app/Contents/Resources COMPONENT ${TARGET})

install(TARGETS ${APP_NAME_LC}
        BUNDLE DESTINATION .
        RUNTIME DESTINATION bin)
set(APPS "\${CMAKE_INSTALL_PREFIX}/bin/${APP_NAME}")
install(CODE "include(BundleUtilities)
              fixup_bundle(\"${APPS}\" \"\" \"\")")

set(CPACK_GENERATOR Bundle)
set(CPACK_BUNDLE_NAME ${APP_NAME})
set(CPACK_BUNDLE_ICON ${CMAKE_CURRENT_BINARY_DIR}/kodi.icns)
set(CPACK_BUNDLE_PLIST ${CMAKE_CURRENT_BINARY_DIR}/Info.plist)
#set(CPACK_DMG_DS_STORE ${CORE_SOURCE_DIR}/tools/darwin/packaging/osx/VolumeDSStoreApp)
set(CPACK_DMG_VOLUME_NAME ${APP_NAME})
set(CPACK_DMG_FORMAT UDZO)
set(CPACK_DMG_BACKGROUND_IMAGE ${CORE_SOURCE_DIR}/tools/darwin/packaging/media/osx/background/DiskImageBackgroundKodi.png)
include(CPack)
