HEADERS = csm.h Error.h Warning.h Version.h Isd.h BytestreamIsd.h NitfIsd.h Plugin.h Model.h GeometricModel.h RasterGM.h CorrelationModel.h FourParameterCorrelationModel.h LinearDecayCorrelationModel.h

OBJS = Version.o Plugin.o GeometricModel.o RasterGM.o CorrelationModel.o FourParameterCorrelationModel.o LinearDecayCorrelationModel.o Isd.o

LIBNAME=libcsmapi
LIBVERSION=3

DOXYGEN_OUT=/programs/origin/html/doxygen/csm3
DOXYGEN_FILTER=$(PWD)/scripts/doxygen-filter.pl

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
	@echo $(LIBRARY)
	@echo $@
	$(LD) $(COPTS) $(LDOPTS) $^ $(LIBS) -o $(LIBRARY)

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
	$(TAR) -czvf csm3.$(shell date '+%Y%m%d').tar.gz Makefile* $(HEADERS) $(OBJS:.o=.cpp) Doxyfile scripts/doxygen-filter.pl

DOXYFILE=$(INSTDIR)/include/Doxyfile

doxygen::
	cat Doxyfile > $(DOXYFILE)
	echo "OUTPUT_DIRECTORY       = $(DOXYGEN_OUT)" >> $(DOXYFILE)
	echo "INPUT_FILTER           = $(DOXYGEN_FILTER)" >> $(DOXYFILE)
	rm -rf $(DOXYGEN_OUT)
	cd $(dir $(DOXYFILE)) && doxygen

