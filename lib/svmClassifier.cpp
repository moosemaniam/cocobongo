#include "svmClassifier.hpp"

svmContext::svmContext(CvSVMParams argparams,int nLables)
{
    params = argparams;
    numberOfLabels = nLables;
}
