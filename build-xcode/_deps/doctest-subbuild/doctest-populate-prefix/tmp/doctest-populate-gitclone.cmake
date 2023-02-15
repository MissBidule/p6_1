# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitclone-lastrun.txt" AND EXISTS "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitinfo.txt" AND
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitclone-lastrun.txt" IS_NEWER_THAN "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/opt/homebrew/bin/git" 
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/doctest/doctest" "doctest-src"
    WORKING_DIRECTORY "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/doctest/doctest'")
endif()

execute_process(
  COMMAND "/opt/homebrew/bin/git" 
          checkout "b7c21ec5ceeadb4951b00396fc1e4642dd347e5f" --
  WORKING_DIRECTORY "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'b7c21ec5ceeadb4951b00396fc1e4642dd347e5f'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/opt/homebrew/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitinfo.txt" "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/doctest-populate-gitclone-lastrun.txt'")
endif()
