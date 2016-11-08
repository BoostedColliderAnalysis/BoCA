#
# Copyright (C) 2015-2016 Jan Hajer
#
create_dictionary(Colors Colors.cpp Colors.hh LinkDef.hh boca plotting)

set(plot_sources
Significance.cpp
Result.cpp
Results.cpp
Plot.cpp
Plots.cpp
Orientation.cpp
Legend.cpp
Canvas.cpp
Histograms.cpp
Histogram2Dim.cpp
Profile.cpp
Graphs.cpp
Style.cpp
Font.cpp
PlottingBase.cpp
)
create_library(Plot plot_sources)
