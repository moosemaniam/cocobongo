#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/core/core.hpp"

#ifndef SVM_CLASSIFIER_H
#define SVM_CLASSIFIER_H
using namespace cv;

typedef enum SVM_LABELS_type
{
    COCONUT,
    NOT_COCONUT
}svm_labels;

class svmContext
{
    public:
        int numberOfLabels;
        CvSVM SVM;
        CvSVMParams params;
        svmContext(CvSVMParams argparams, int nLables);
};
#endif
