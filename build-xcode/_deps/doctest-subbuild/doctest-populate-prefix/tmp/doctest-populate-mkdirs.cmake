# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-src"
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-build"
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix"
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/tmp"
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp"
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src"
  "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/liloualidor/Documents/IMAC/annee_2/POO/S4/p6_1/build-xcode/_deps/doctest-subbuild/doctest-populate-prefix/src/doctest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
