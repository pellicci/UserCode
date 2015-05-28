ROOTCFLAGS    = $(shell /usr/bin/root-config --cflags)
ROOTLIBS      = $(shell /usr/bin/root-config --libs)
ROOTGLIBS     = $(shell /usr/bin/root-config --glibs)

CXX           = g++
CXXFLAGS      = -g -Wall -fPIC
CXXFLAGS      = -g -Wall -fPIC
LD            = g++
LDFLAGS       = -g
SOFLAGS       = -shared

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
gGLIBS          = $(filter-out -lNew, $(NGLIBS))

CXXFLAGS      += $(ROOTCFLAGS)
CXX           += -I./
LIBS           = $(ROOTLIBS) 

NGLIBS         = $(ROOTGLIBS) 
NGLIBS        += -lMinuit
GLIBS          = $(filter-out -lNew, $(NGLIBS))

.SUFFIXES: .cc,.C

.C.o:
	$(CXX) $(CXXFLAGS) -c -I. $<



DDmix:  DDmix.cc  
	$(CXX) $(CXXFLAGS) -c -I. $<
	$(LD) $(LDFLAGS) -o DDmix DDmix.o  $(GLIBS)

2dplot: analysis.cc  
	$(CXX) $(CXXFLAGS) -c -I. $<
	$(LD) $(LDFLAGS) -o 2dplot analysis.o  $(GLIBS)

1dplot: make1Dplots.cc
	$(CXX) $(CXXFLAGS) -o 1Dplot $(NGLIBS) $<

 
# ================================================================================
clean:
	rm -f DDmix.o  DDmix
	rm -f *~
