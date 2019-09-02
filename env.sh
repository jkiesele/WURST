
SCRIPT=$(readlink -f "$0")
WURSTDIR=$(dirname "${SCRIPT}")

cd /afs/cern.ch/user/j/jkiesele/public/DAnalysis_framework/v.1.1_rc2_cc7/CMSSW_10_5_0
eval `scramv1 runtime -sh`
cd ..
export PYTHIA8=$CMSSW_RELEASE_BASE/../../../external/pythia8/240-nmpfii
export LD_LIBRARY_PATH=$PYTHIA8/lib:$LD_LIBRARY_PATH

export FASTJET=$CMSSW_RELEASE_BASE/../../../external/fastjet/3.3.0-pafccj
export LD_LIBRARY_PATH=$FASTJET/lib:$LD_LIBRARY_PATH

cd $WURSTDIR