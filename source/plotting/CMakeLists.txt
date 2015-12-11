#
# Copyright (C) 2015 Jan Hajer
#
add_include_path(../../include/)
set(plot_sources
Plotting.cpp
Result.cpp
Legend.cpp
LatexFile.cpp
Canvas.cpp
Histograms.cpp
Graphs.cpp
Style.cpp
Font.cpp
Graph.cpp
)
create_library(Plot plot_sources)
