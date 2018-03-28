//Authors: Dario Cattaruzza, Alessandro Abate, Peter Schrammel, Daniel Kroening
//University of Oxford 2016
//This code is supplied under the BSD license agreement (see license.txt)

#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H
#include "Scalar.h"
#include <map>

namespace abstract
{

class ProgramOptions {
public:
  ProgramOptions(int argc, char *argv[]);
  void process();
  void help(std::ostream &out);
  std::string getVersion();
  std::list<numericType_t>          types;
  optionList_t                      options;
  stringList                        files;
  synthesisType_t                   synthType;
  displayType_t                     displayType;
  space_t                           space;
  canonicalType_t                   useCanonicalForm;
  bvType_t                          bvType;
  bool                              traceIntervals;
  bool                              formal;
  bool                              incremental;
  bool                              continuous;
  bool                              answerOnly;
  bool                              useConsole;
  bool                              useBasis;
  bool                              useSparse;
  bool                              aggressive;
  bool                              parseError;
};

}

#endif // PROGRAM_OPTIONS_H
