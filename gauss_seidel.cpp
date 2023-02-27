#include "gauss_seidel.h"

#include <opencv4/opencv2/core/matx.hpp>

inline uchar Clamp(int n) {
    n = n > 255 ? 255 : n;
    return n < 0 ? 0 : n;
}

inline Vec3b SampleAt(Mat const &mSrc, int Row, int Col) {
    Row = Row >= 0 ? (Row >= mSrc.rows ? mSrc.rows - 1 : Row) : 0;
    Col = Col >= 0 ? (Col >= mSrc.cols ? mSrc.cols - 1 : Col) : 0;
    return mSrc.at<Vec3b>(Row, Col);
}

bool GaussSeidel_Seq(const Mat mSrc, Mat &mDst) {
    if (mSrc.empty()) {
        cout << "[Error]! Input Image Empty!";
        return false;
    }

    if (mSrc.rows > mSrc.cols) {
        cout << "[Error]! #Rows > #Cols not supported by GaussSeidel"
                "operations"
             << endl;
        return false;
    }

    // Ascendance par ligne (Partie I)
    for (int Diag = 0; Diag < mSrc.rows; Diag++) {
        for (int Row = 0; Row <= Diag; Row++) {
            int Col = Diag - Row;
            Vec3b &Des_Pixel = mDst.at<Vec3b>(Row, Col);
            Des_Pixel = {0, 0, 0};

            // Debug
            Des_Pixel.val[0] = 255;
            Des_Pixel.val[1] = 0;
            Des_Pixel.val[2] = 0;

            // Itération courante
            // Des_Pixel += SampleAt(mSrc, Row - 1, Col);
            // Des_Pixel += SampleAt(mSrc, Row, Col - 1);

            // // Itération précedente
            // Des_Pixel += SampleAt(mSrc, Row, Col);
            // Des_Pixel += SampleAt(mSrc, Row + 1, Col);
            // Des_Pixel += SampleAt(mSrc, Row, Col + 1);

            // // Normalisation
            // for (int c = 0; c < 3; c++) {
            //     Des_Pixel.val[c] /= 1;
            // }
        }
    }

    // Translation du milieu (Partie II)
    for (int Diag = mSrc.rows; Diag < mSrc.cols; Diag++) {
        for (int Row = 0; Row < mSrc.rows; Row++) {
            int Col = Diag - Row;
            Vec3b &Des_Pixel = mDst.at<Vec3b>(Row, Col);
            Des_Pixel.val[0] = 0;
            Des_Pixel.val[1] = 255;
            Des_Pixel.val[2] = 0;

            // Des_Pixel += SampleAt(mSrc, Row, Col);
        }
    }

    // Descendance par colonne (Partie III)
    // Le 1 est pour éviter la coupure avec le milieu
    for (int t = 1; t < mSrc.rows; t++) {
        int Diag = mSrc.cols + t - 1;
        for (int Row = t; Row < mSrc.rows; Row++) {
            int Col = Diag - Row;
            Vec3b &Des_Pixel = mDst.at<Vec3b>(Row, Col);
            Des_Pixel.val[0] = 0;
            Des_Pixel.val[1] = 0;
            Des_Pixel.val[2] = 255;

            // Des_Pixel += SampleAt(mSrc, Row, Col);
        }
    }

    return true;
}
