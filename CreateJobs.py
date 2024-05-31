import os, sys

def createdirs(num,dataset):
  os.system("mkdir /eos/user/g/gmarozzo/test/"+dataset+"_Chunk"+str(cDATA))
  os.system("cp -r Condor_Template "+dataset+"_Chunk"+str(cDATA))
  os.system("sed -i 's/AAAAA/"+line.split("/")[7].strip()+"/g' "+dataset+"_Chunk"+str(cDATA)+"/batchScript.sh")
  os.system("sed -i 's/BBBBB/"+line.split("/")[8].strip()+"/g' "+dataset+"_Chunk"+str(cDATA)+"/batchScript.sh")
  os.system("sed -i 's/CCCCC/"+str(num)+"/g' "+dataset+"_Chunk"+str(cDATA)+"/batchScript.sh")
  print("Created "+dataset+"_Chunk"+str(cDATA))

filelist3 = open("filelistTau.txt","r")
cDATA=0
for line in filelist3:
  cDATA=cDATA+1
  
  if(cDATA < 30): createdirs(1,"HtoTauTau")
  elif(cDATA < 119): createdirs(2,"HtoTauTau_EE")
  #if(cDATA < 119): continue
  elif(cDATA < 306): createdirs(3,"TTsemilep")
  elif(cDATA < 829): createdirs(4,"TTsemilep_EE")
  
filelist3.close()
