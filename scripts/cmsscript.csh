ssh -t pellicci@lxplus.cern.ch -L 1081:localhost:1081 "ssh -ND 1081 dtdqm@cmsusr"



ssh -t dtdqm@lxplus.cern.ch -L 1080:localhost:1081 "ssh -ND 1081 dtdqm@cmsusr"
