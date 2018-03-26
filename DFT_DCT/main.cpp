
#include "variables.h"

// function declarations
/*
calculateDFT : calculates the DFT of an image given using the opencv dft command.
However, this DFT has it's center on the top-left corner. This needs to be recentered for visualization and
processing purposes.
*/
void calculateDFT(Mat& source, Mat& destination){

source.convertTo(src_float,CV_32FC1, 1.0/255.0);
Mat dst_complex[2]={src_float,Mat::zeros(src_float.size(), CV_32F)};
merge(dst_complex, 2, dft_setup);
dft(dft_setup, destination,DFT_COMPLEX_OUTPUT);

}
/* maskmagnitudeDFT: masks the DFT and calculates the magnitude of the DFT*/
void maskmagnitudeDFT(Mat&source, int X){
Mat s_array[2]={Mat::zeros(source.size(),CV_32F),Mat::zeros(source.size(),CV_32F)};
//int L_min = 30;
int L = 128-X;
for (int r=L;r< 255-L+1;r++){
for(int c=0;c<256;c++){
    source.at<Vec2f>(r,c)= source.at<Vec2f>(r,c)*0.0;
}
}
for (int r=0;r< 256;r++){
for(int c=L;c<255-L+1;c++){
    source.at<Vec2f>(r,c)= source.at<Vec2f>(r,c)*0.0;
}
}
split(source, s_array);
magnitude(s_array[0], s_array[1], dft_mag);
dft_mag+=Scalar::all(1);
log(dft_mag,dft_mag);
normalize(dft_mag,dft_mag,0,1,CV_MINMAX);

}

void recenterDFT( ){
int xCenter= dft_mag.cols/2;
int yCenter = dft_mag.rows/2;

Mat q1(dft_mag,Rect(0,0,xCenter,yCenter));
Mat q2(dft_mag,Rect(xCenter,0,xCenter,yCenter));
Mat q3(dft_mag,Rect(0,yCenter,xCenter,yCenter));
Mat q4(dft_mag,Rect(xCenter,yCenter,xCenter,yCenter));

Mat temp;
q1.copyTo(temp);
q4.copyTo(q1);
temp.copyTo(q4);

q2.copyTo(temp);
q3.copyTo(q2);
temp.copyTo(q3);
}

void invertDFT(Mat& source,Mat& destination){
dft(source, destination,DFT_INVERSE|DFT_REAL_OUTPUT|DFT_SCALE);
normalize(destination, destination, 0, 1, CV_MINMAX);
}

void calculateDCT(int k){
dct(src_float, dct_float);
imshow("DCT",dct_float);
for (int r=0;r< 255;r++){
for(int c=0;c<255;c++){
if(r<=k && c<=k){
dct_float.at<float>(r,c)= dct_float.at<float>(r,c);
}
else{
dct_float.at<float>(r,c)= dct_float.at<float>(r,c)*0.0;

}
}
}
idct(dct_float, dct_reconstruction);

}

void getMSE( Mat& I1,  Mat& I2,const char* method)
{
    Mat s1;
    
    absdiff(I1, I2, s1);
    s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
    s1 = s1.mul(s1);           // |I1 - I2|^2
    Scalar s = sum(s1);        // sum elements per channel

    
    double sse = s.val[0];
    double mse  = sse / (double)(I1.total());
    printf("MSE from %s reconstruction = %f\n",method, mse);
    
}
int main(int argc, char** argv)
{
int l=0,k=0;
filename = "zebras.jpg";
src = imread(filename, 0);
cout<<"Enter the value of L for DFT: \n";
cin >> l;
    cout<<"Enter the value of L for DCT: \n";
    cin >> k;
if(l>128){
l = l-128;
}
if(src.empty())
{

cout << "can not open " << filename << endl;  //check if the file is empty
return -1;
}
calculateDFT(src, dft_dst);
maskmagnitudeDFT(dft_dst,l);
recenterDFT();
invertDFT(dft_dst,inverseDFT);
calculateDCT(k);
    d = "DFT";
    getMSE(src_float, inverseDFT,d);
    d="DCT";
    getMSE(src_float, dct_reconstruction,d);

imshow("Source Image", src);
imshow("DFT Magnitude", dft_mag);
imshow("Inverse DFT", inverseDFT);
imshow("Masked DCT",dct_float);
imshow("Inverse DCT",dct_reconstruction);
waitKey();
return 0;
}
