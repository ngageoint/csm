ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libcsmapi.la

libcsmapi_la_SOURCES = \
  BundleGM.cpp \
  ConstantCorrelationFunction.cpp \
  CorrelationModel.cpp \
  DampedCosineCorrelationFunction.cpp \
  Ellipsoid.cpp \
  FourParameterCorrelationFunction.cpp \
  FourParameterCorrelationModel.cpp \
  GeometricModel.cpp \
  Isd.cpp \
  LinearDecayCorrelationFunction.cpp \
  LinearDecayCorrelationModel.cpp \
  ModelIdentifier.cpp \
  MultiFunctionCorrelationModel.cpp \
  MultiNitfIsd.cpp \
  Plugin.cpp \
  PointCloudGM.cpp \
  PointCloudIsd.cpp \
  RasterGM.cpp \
  SettableEllipsoid.cpp \
  Version.cpp \
  WeightedSumCorrelationFunction.cpp \
  csmPointCloud.cpp

libcsmapi_la_CPPFLAGS =
if ENABLE_LEGACY_CXX11_ABI
libcsmapi_la_CPPFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
endif

libcsmapi_la_CXXFLAGS = -Wall -std=c++11
libcsmapi_la_LDFLAGS = -version-info 4:0:1
libcsmapi_la_LIBADD = -lm $(DL_LIBS)

csmincludedir = $(includedir)/csm
csminclude_HEADERS = \
  BundleGM.h \
  BytestreamIsd.h \
  ConstantCorrelationFunction.h \
  CorrelationModel.h \
  DampedCosineCorrelationFunction.h \
  Ellipsoid.h \
  Error.h \
  FourParameterCorrelationFunction.h \
  FourParameterCorrelationModel.h \
  GeometricModel.h \
  Isd.h \
  LinearDecayCorrelationFunction.h \
  LinearDecayCorrelationModel.h \
  Model.h \
  ModelIdentifier.h \
  MultiFunctionCorrelationModel.h \
  MultiNitfIsd.h \
  NitfIsd.h \
  Plugin.h \
  PointCloudGM.h \
  PointCloudIsd.h \
  RasterGM.h \
  SPDCorrelationFunction.h \
  SettableEllipsoid.h \
  Version.h \
  Warning.h \
  WeightedSumCorrelationFunction.h \
  csm.h \
  csmPointCloud.h

noinst_HEADERS = contrib/CSMRasterWithRangeGM.h

dist_doc_DATA = LICENSE README

EXTRA_DIST = \
  Doxyfile \
  scripts/doxygen-filter.pl \
  scripts/mscc \
  scripts/mslink \
  scripts/objects_to_def

DOXYGEN_CONFIG = Doxyfile.autotools
DOXYGEN_OUTPUT = $(abs_builddir)/doxygen
DOXYGEN_EXCLUDES = $(abs_builddir)/_install $(abs_builddir)/autom4te.cache $(abs_builddir)/build-aux $(abs_builddir)/doxygen $(abs_builddir)/m4

.PHONY: doxygen
doxygen:
	@if test "x$(DOXYGEN)" = "x:"; then \
	  echo "doxygen not found"; \
	  exit 1; \
	fi
	cp $(srcdir)/Doxyfile $(DOXYGEN_CONFIG)
	echo "OUTPUT_DIRECTORY = $(DOXYGEN_OUTPUT)" >> $(DOXYGEN_CONFIG)
	echo "INPUT = $(abs_srcdir)" >> $(DOXYGEN_CONFIG)
	echo "INPUT_FILTER = $(abs_srcdir)/scripts/doxygen-filter.pl" >> $(DOXYGEN_CONFIG)
	echo "STRIP_FROM_INC_PATH = $(abs_srcdir)" >> $(DOXYGEN_CONFIG)
	echo "EXCLUDE = $(DOXYGEN_EXCLUDES)" >> $(DOXYGEN_CONFIG)
	$(DOXYGEN) $(DOXYGEN_CONFIG)

CLEANFILES = $(DOXYGEN_CONFIG)
