

HEADERS = csm.h Error.h Warning.h Version.h Isd.h BytestreamIsd.h NitfIsd.h Plugin.h Model.h GeometricModel.h RasterGM.h CovarianceModel.h FourParameterCorrelationModel.h LinearDecayCorrelationModel.h

OBJS = Version.o Plugin.o GeometricModel.o RasterGM.o FourParameterCorrelationModel.o LinearDecayCorrelationModel.o

LIBNAME=libcsmapi
LIBVERSION=3

LIBRARY=$(LIBNAME).so.$(LIBVERSION)
LIBS=-lm -ldl

MKDIR=mkdir
CP=cp -f
LN=ln -s
TAR=tar

LD=$(CC)

%.o: %.cpp
	$(CC) -c $(COPTS) $< -o $@

%.o: %.cc
	$(CC) -c $(COPTS) $< -o $@

$(LIBRARY): $(OBJS)
	$(LD) $(COPTS) $(LDOPTS) $^ $(LIBS) -o $@

all: $(HEADERS) $(LIBRARY)

install::
	$(MKDIR) -p $(INSTDIR)/lib
	$(CP) $(LIBRARY) $(INSTDIR)/lib
	$(RM) $(INSTDIR)/lib/$(LIBNAME).so && $(LN) $(LIBRARY) $(INSTDIR)/lib/$(LIBNAME).so
	$(MKDIR) -p $(INSTDIR)/include/csm
	$(CP) $(HEADERS) $(INSTDIR)/include/csm

clean::
	$(RM) $(OBJS) $(LIBRARY) *~

package::
	$(TAR) -czvf csm-reform.$(shell date '+%Y%m%d').tar.gz Makefile* $(HEADERS) $(OBJS:.o=.cpp)
