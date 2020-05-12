#
# File: GeoPlanetLib/CMakeCopyDlls.cmake
#
# This file was copied from: https://github.com/dormon/cmakeTutorial/blob/master/examples/09-CopyDll/CMakeLists.txt
# This header and prevention of fail on not found dlls was added.
#

function(getSharedLibraries out lib cfg)
  # message("getSharedLibraries(${lib} ${cfg})")

  if(TARGET ${lib})
    get_target_property(target_type ${lib} TYPE)
    if(${target_type} STREQUAL "INTERFACE_LIBRARY")
      # message("${lib} JE ${target_type}")
      return()
    endif()
  else()
     # message("${lib} NENI TARGET")
    return()
  endif()


  get_target_property(dll ${lib} IMPORTED_LOCATION_${cfg})
  list(APPEND dlls ${dll})

  get_target_property(interfaceLibs ${lib} INTERFACE_LINK_LIBRARIES)
  if(NOT "${interfaceLibs}" STREQUAL "interfaceLibs-NOTFOUND")
    foreach(interfaceLib ${interfaceLibs})
      getSharedLibraries(ilibs ${interfaceLib} ${cfg})
      list(APPEND dlls ${ilibs})
    endforeach()
  endif()
  list(REMOVE_DUPLICATES dlls)
  set(${out} ${dlls} PARENT_SCOPE)
endfunction()


function(getAllSharedLibraries allLibraries app cfg)
  get_target_property(libs ${app} LINK_LIBRARIES)
  foreach(lib ${libs})
    getSharedLibraries(libList ${lib} ${cfg})
    # message("${lib} ###### ${libList}")
    list(APPEND allLibs ${libList})
  endforeach()
  list(REMOVE_DUPLICATES allLibs)
  set(${allLibraries} ${allLibs} PARENT_SCOPE)
endfunction()

getAllSharedLibraries(allDebugSharedLibraries ${PROJECT_NAME} DEBUG)
getAllSharedLibraries(allReleaseSharedLibraries ${PROJECT_NAME} RELEASE)

# message("SharedDebug  : ${allDebugSharedLibraries}")
# message("SharedRelease: ${allReleaseSharedLibraries}")

if(MSVC)
    if (NOT DEFINED OUTPUT_BINDIR)
        set(OUTPUT_BINDIR ${CMAKE_CURRENT_BINARY_DIR})
    endif()
    foreach(lib ${allDebugSharedLibraries})
        if (EXISTS ${lib})
            message("loading dll: ${lib}")
            file(COPY ${lib} DESTINATION ${OUTPUT_BINDIR}/Debug)
        endif()
    endforeach()
    foreach(lib ${allReleaseSharedLibraries})
        if (EXISTS ${lib})
            message("loading dll: ${lib}")
            file(COPY ${lib} DESTINATION ${OUTPUT_BINDIR}/Release)
        endif()
    endforeach()
endif()

# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
# install(FILES ${allReleaseSharedLibraries} DESTINATION .)
