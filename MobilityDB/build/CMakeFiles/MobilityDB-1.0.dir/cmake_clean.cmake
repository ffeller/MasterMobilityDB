file(REMOVE_RECURSE
  "libMobilityDB-1.0.pdb"
  "libMobilityDB-1.0.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/MobilityDB-1.0.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
