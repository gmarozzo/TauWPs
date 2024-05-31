Repo for Working Point computations for Tau POG.

# Running on HTCondor

The CreateJobs.py script creates one condor job for each input file. Currently it is setup for 2022 and 2022EE H->TauTau MC samples. To submit these jobs:

```bash
csh resubmit_Condor.csh
```

The checkProd.csh can be used to check the status of the jobs, and will move the successfully completed ones to the newly created AAAOK subdirectory. When all jobs have finished (can be checked with condor_q), if some have failed you can run the cleanup.csh and then resubmit as before.  

When all the jobs have been successfully completed and checkProd.csh has been run, you can run:

```bash
python3 hadd.py AAAOK
```

# Running in local

The TauEffForPOG.C can be (re)compiled with:

```bash
g++ -o "TauEffForPOG.exe" "TauEffForPOG.C" $(root-config --cflags --glibs) 
```

After that, it can be run with: 

```bash
./TauEffForPog.exe "" "0"
```

This will create a testoutput.root file, which can then be analyzed to extract the efficiencies.

# Extracting efficiencies

In the "macros" subdirectory, you can find ROOT macros for the efficienies. The "getTauWP.C" macro will compute the efficiency for every bin declared in the TauEffForPog.C

