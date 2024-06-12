import os, sys

def createdirs(era,sample):
  os.system("ls /eos/cms/store/group/phys_higgs/HLepRare/HTT_skim_v1/Run2_"+era+"/"+sample+"/ > log.txt")
  with open("log.txt",'r') as file:
    Lines = file.readlines()
    counter=0
    for line in Lines:
      counter=counter+1
      if ".root" in line:
        os.system("mkdir /eos/user/g/gmarozzo/test/"+sample+"_"+era+"_Chunk"+str(counter))
        os.system("cp -r Condor_Template "+sample+"_"+era+"_Chunk"+str(counter))
        with open(sample+"_"+era+"_Chunk"+str(counter)+"/batchScript.sh",'r') as file:                                                                                      
          filedata=file.read()                                                                                                                                                                         
          filedata = filedata.replace('AAAAA',"root://eoscms.cern.ch//eos/cms/store/group/phys_higgs/HLepRare/HTT_skim_v1/Run2_"+era+"/"+sample+"/"+line.strip())                                                                                                                                          
        with open(sample+"_"+era+"_Chunk"+str(counter)+"/batchScript.sh",'w') as file:
          file.write(filedata)        
        print("Created "+sample+"_"+era+"_Chunk"+str(counter))

for year in ["2016","2016_HIPM","2017","2018"]:
  for dataset in ["TTToSemiLeptonic","GluGluHToTauTau_M125"]:
    createdirs(year,dataset)
