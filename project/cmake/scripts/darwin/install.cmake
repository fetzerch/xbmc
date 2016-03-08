# OSX packaging

set(PACKAGE_OUTPUT_DIR ${CORE_SOURCE_DIR}/build/${CORE_BUILD_CONFIG})

add_custom_target(osx_copyrootfiles
    COMMAND "ACTION=build"
            "TARGET_BUILD_DIR=${PACKAGE_OUTPUT_DIR}"
            "TARGET_NAME=${APP_NAME}.app"
            "APP_NAME=${APP_NAME}"
            "SRCROOT=${CMAKE_BINARY_DIR}"
            ${CORE_SOURCE_DIR}/tools/darwin/Support/CopyRootFiles-osx.command)

configure_file(${CORE_SOURCE_DIR}/xbmc/platform/darwin/osx/Info.plist.in
               ${CMAKE_BINARY_DIR}/xbmc/platform/darwin/osx/Info.plist @ONLY)
execute_process(COMMAND perl -p -i -e "s/r####/${APP_SCMID}/" ${CMAKE_BINARY_DIR}/xbmc/platform/darwin/osx/Info.plist)
add_custom_target(osx_copyframeworks
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${APP_NAME_LC}> ${PACKAGE_OUTPUT_DIR}/${APP_NAME}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${CORE_BUILD_DIR}/DllPaths_generated.h
                                     ${CMAKE_BINARY_DIR}/xbmc/DllPaths_generated.h
    COMMAND "XBMC_DEPENDS=${DEPENDS_PATH}"
            "TARGET_BUILD_DIR=${PACKAGE_OUTPUT_DIR}"
            "TARGET_NAME=${APP_NAME}.app"
            "APP_NAME=${APP_NAME}"
            "FULL_PRODUCT_NAME=${APP_NAME}.app"
            "SRCROOT=${CMAKE_BINARY_DIR}"
            ${CORE_SOURCE_DIR}/tools/darwin/Support/copyframeworks-osx.command)
add_dependencies(osx_copyframeworks osx_copyrootfiles)

# Usually executed from CI (packaging script). Hardcodes path for in source builds.
# Builds dmg into same directory in source tree.
configure_file(${CORE_SOURCE_DIR}/tools/darwin/packaging/osx/mkdmg-osx.sh.in
               ${CORE_SOURCE_DIR}/tools/darwin/packaging/osx/mkdmg-osx.sh @ONLY)
add_custom_target(osx_makedmg
    COMMAND "SUDO=/usr/bin/sudo" sh ./mkdmg-osx.sh ${CORE_BUILD_CONFIG}
    WORKING_DIRECTORY ${CORE_SOURCE_DIR}/tools/darwin/packaging/osx)
add_dependencies(osx_makedmg osx_copyframeworks)
