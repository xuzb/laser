#include "../ModuleLoader/src/ModuleLoader.h"
#include "FunctionSimulator.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Support/CommandLine.h"

using namespace laser;

static llvm::cl::list<std::string>
InputFilenames(llvm::cl::Positional, llvm::cl::desc("<input preprocessed files>"));

class AnalysisEngine : public CallGraphSCCPass {
  static char Pid;
  
public:
  AnalysisEngine() : CallGraphSCCPass(Pid) {}
  bool runOnSCC(CallGraphSCC &scc);
};

char AnalysisEngine::Pid = 0;

bool AnalysisEngine::runOnSCC(CallGraphSCC &scc) {
  for (CallGraphSCC::iterator i = scc.begin(),
                              e = scc.end(); i != e; ++i) {
    CallGraphNode *cgnode = *i;
    Function *f = cgnode->getFunction();
    FunctionSimulator fsimulator(f);
    fsimulator.simulate();
  }
}

bool RegisterAnalysisEngine(PassManager &passMgr) {
  PassRegistry &Registry = *PassRegistry::getPassRegistry();
  INITIALIZE_AG_DEPENDENCY(CallGraph)
  AnalysisEngine *engine = new AnalysisEngine();
  passMgr.add(engine);
}

int main(int argc, char **argv) {
  llvm::cl::ParseCommandLineOptions(argc, argv, "main");
  ModuleLoader mloader(getGlobalContext());
  Module *module = mloader.loadInputFiles(InputFilenames);
  if (module == NULL) {
    mloader.dumpErrorMessages();
    return 0;
  }

  PassManager passMgr;
  RegisterAnalysisEngine(passMgr);
  passMgr.run(*module);
  return 0;
}
