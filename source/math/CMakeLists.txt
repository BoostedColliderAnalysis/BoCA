#
# Copyright (C) 2015-2016 Jan Hajer
#
add_include_path(../../include/)
set(MathSources
Math.cpp
LorentzVector.cpp
LorentzVectorBase.cpp
Vector3.cpp
Vector2.cpp
)
create_library(Math MathSources)

