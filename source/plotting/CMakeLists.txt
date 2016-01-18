#
# Copyright (C) 2015 Jan Hajer
#
add_include_path(../../include/)
set(plot_sources
Plotting.cpp
Result.cpp
Results.cpp
Plot.cpp
Plots.cpp
Legend.cpp
LatexFile.cpp
Canvas.cpp
Histograms.cpp
Histogram2Dim.cpp
Profile.cpp
Graphs.cpp
Style.cpp
Font.cpp
)
create_library(Plot plot_sources)
