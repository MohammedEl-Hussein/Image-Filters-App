/*
Name: Sherif Ahmed Eisa
ID: 20230190
Section: 2
Filters he did: 1- Grayscale Filter
                2- Brightness Filter
                3- Merge Filter
                4- Edge Detection Filter
                5- Sunlight Filter

Name: Mohammed El-Hussein Taha
ID: 20230323
Section: 1
Filters he did: 1- Invert Image Filter
                2- Blur Filter
                3- Frame Filter
                4- Rotate Filter
                5- Lighter Purple Filter


Name: Farida Ahmed Abd El-Aziz
ID: 20231121
Section: 2
Filters she did:1- Black and White Filter
                2- crop
                3- resize
                4- flipping filter
                5- infrared

 */

#include <iostream>
#include <cmath>
#include "Image_Class.h"
using namespace std;

// Function prototypes
void grayscaleFilter(Image& image);
void brightnessFilter(Image& image);
void invertImageFilter(Image& image);
void blurFilter(Image& image);
void blackAndWhiteFilter(Image& image);
void applyFrame(const string& filename, int choice);
void applyLighterPurpleFilter(Image& image, const string& filename);
void rotateImage(const string& filename, int degree);
void crop(Image &image, int z, int y, int width, int height);
void Infrared(Image& image);
void resize(Image& img1, int NH, int NW);
void flip_horizontal(Image& image);
void flip_vertical(Image& image);
void Merge (Image& image,Image& pic2);
void sunlightFilter(Image& image);
void EdgeDetection( Image& x);
int main() {
    while (true) {
        cout << "Enter the image name with its extension:";
        string img, img2, choiceSave;
        cin>>img;
        Image x(img);
        cout << "1) Grayscale Filter\n2) Brightness Filter\n3) Invert Image Filter\n4) Blur Filter\n5) Black & White Filter\n6) Apply Frame\n7) Lighter Purple Filter\n8) Rotate Image Filter\n9) Crop Image\n10) Infrared Filter\n11) Resize Image\n12) Flipping\n13) Merge Filter\n14)sunlight Filter\n15)Edge Detection\n16) Exit\n";
        int choiceMenu;
        cin >> choiceMenu;
        if (choiceMenu == 16) {
            cout << "Goodbye!";
            break;
        } // Exit the program
        if (choiceMenu==13) {
            cout << "Enter the name of the second image with its extension: ";
            cin >> img2;
            Image pic1(img);
            Image pic2(img2);
            Merge(x, pic2);
            cout << "Do you want to save the new file? Y/N\n";
            cin >> choiceSave;
            if (choiceSave == "n" || choiceSave == "N") {
                x.saveImage(img);
            } else if (choiceSave == "y" || choiceSave == "Y") {
                cout << "Enter the new image name to store it with its extension: ";
                cin >> img2;
                x.saveImage(img2);
                cout<<"Image saved as:"<<img2 <<"\n";
            }

            continue;
        }
        if (choiceMenu == 8){
            int degree;
            cout << "Enter the degree you want to rotate (90, 180, 270): ";
            cin >> degree;

            rotateImage(img, degree);
            continue;

        }
        if (choiceMenu == 6) {
            int frameChoice;
            cout << "1) Classic Frame\n2) Fancy Frame\n";
            cout << ">>";
            cin >> frameChoice;
            applyFrame(img, frameChoice);
            continue;
        }


        switch (choiceMenu) {
            case 1:
                grayscaleFilter(x);
                break;
            case 2:
                brightnessFilter(x);
                break;
            case 3:
                invertImageFilter(x);
                break;
            case 4:
                blurFilter(x);
                break;
            case 5:
                blackAndWhiteFilter(x);
                break;
            case 7:
                applyLighterPurpleFilter(x, img);
                break;
            case 15:
                EdgeDetection( x);
                break;
            case 14:
                sunlightFilter(x);
                break;
            case 12:
                int dir;
                cout << "Select the flipping direction: "<<endl;
                cout << "1) Flip Horizontally"<<endl;
                cout << "2) Flip Vertically" <<endl;
                cin >>dir;
                if(dir == 1){
                    flip_horizontal(x);
                }
                else if(dir == 2){
                    flip_vertical(x);
                }
                else{
                    cout << "Invalid choice" <<endl;
                }
                break;

            case 11:
                int newHeight, newWidth;
                cout << "Enter the new height:\n";
                cin >> newHeight;

                cout << "Enter the new width: ";
                cin >> newWidth;

                resize(x, newHeight, newWidth);
                break;

            case 10:
                Infrared(x);
                break;

            case 9:
                int z, y, width, height;
                cout << "Enter the starting point (upper left corner) coordinates: ";
                cin >> z >> y;
                cout << "Enter width and height respectively: ";
                cin >> width >> height;
                crop(x,z,y,width,height);
                break;




            default:
                cout << "Invalid choice. Please select again." << endl;
                continue; // Restart the loop
        }

        cout << "Do you want to save the new file? Y/N\n";
        cin >> choiceSave;
        if (choiceSave == "n" || choiceSave == "N") {
            x.saveImage(img);
        } else if (choiceSave == "y" || choiceSave == "Y") {
            cout << "Enter the new image name to store it with its extension: ";
            cin >> img2;
            x.saveImage(img2);
            cout<<"Image saved as:"<<img2 <<"\n";
        }
    }
}

// Function to apply grayscale filter
void grayscaleFilter(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = avg;   // Do the grayscaling
            }
        }
    }
}

// Function to apply brightness filter
void brightnessFilter(Image& image) {
    int choice;
    cout << "1) 50% more bright \n2) 50% less light";
    cin >> choice;
    if (choice == 2) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
// Multiply pixel values by 0.5 to decrease brightness by 50%
                    image(i, j, k) *= 0.5;
                }
            }
        }
    } else if (choice == 1) {
        for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height; ++j) {
                for (int k = 0; k < 3; ++k) {
// Multiply pixel values by 2 to increase brightness by 50%
                    image(i, j, k) *= 2;
                }
            }
        }
    }
}

// Function to invert image
void invertImageFilter(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }
}

// Function to apply blur filter
void blurFilter(Image& image) {
    const int radius = 7; // Radius of the blur filter

    for (int i = radius; i < image.width - radius; ++i) {
        for (int j = radius; j < image.height - radius; ++j) {
            int sum_R = 0, sum_G = 0, sum_B = 0;
            for (int x = -radius; x <= radius; ++x) {
                for (int y = -radius; y <= radius; ++y) {
                    sum_R += image(i + x, j + y, 0);
                    sum_G += image(i + x, j + y, 1);
                    sum_B += image(i + x, j + y, 2);
                }
            }
            int area = (2 * radius + 1) * (2 * radius + 1);
            image(i, j, 0) = sum_R / area;
            image(i, j, 1) = sum_G / area;
            image(i, j, 2) = sum_B / area;
        }
    }
}

// Function to apply black and white filter
void blackAndWhiteFilter(Image& image) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= 3;
            for(int k = 0; k < 3; k++) {
                if(avg < 128) {
                    image.setPixel(i, j, k, 0);
                } else {
                    image.setPixel(i, j, k, 255);
                }
            }
        }
    }
}

// Function to apply frame
void applyFrame(const string& img, int choice) {
    Image image(img);

    if (choice == 1 || choice == 2) {
        int x = (((image.height + image.width) / 2) * 2) / 100;

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < x; j++) {
                image(i, j, 0) = 150;
                image(i, j, 1) = 0;
                image(i, j, 2) = 255;

                image(i, image.height - 1 - j, 0) = 150;
                image(i, image.height - 1 - j, 1) = 0;
                image(i, image.height - 1 - j, 2) = 255;
            }

            if (choice == 2) {
                int y = x-60;
                for (int j = 0; j < y; j++) {
                    image(i, j, 0) = 255;
                    image(i, j, 1) = 255;
                    image(i, j, 2) = 255;

                    image(i, image.height - 1 - j, 0) = 255;
                    image(i, image.height - 1 - j, 1) = 255;
                    image(i, image.height - 1 - j, 2) = 255;
                }
            }
        }

        for (int j = 0; j < image.height; j++) {
            for (int i = 0; i < x; i++) {
                image(i, j, 0) = 150;
                image(i, j, 1) = 0;
                image(i, j, 2) = 255;

                image(image.width - 1 - i, j, 0) = 150;
                image(image.width - 1 - i, j, 1) = 0;
                image(image.width - 1 - i, j, 2) = 255;
            }

            if (choice == 2) {
                int y = x-60;
                for (int i = 0; i < y; i++) {
                    image(i, j, 0) = 255;
                    image(i, j, 1) = 255;
                    image(i, j, 2) = 255;

                    image(image.width - 1 - i, j, 0) = 255;
                    image(image.width - 1 - i, j, 1) = 255;
                    image(image.width - 1 - i, j, 2) = 255;
                }
            }
        }

        string  img2, choiceSave;
        cout << "Do you want to save the new file? Y/N\n";
        cin >> choiceSave;
        if (choiceSave == "n" || choiceSave == "N") {
            image.saveImage(img);
            cout<<"Saved as:"<<img;
        } else if (choiceSave == "y" || choiceSave == "Y") {
            cout << "Enter the new image name to store it with its extension: ";
            cin >> img2;
            image.saveImage(img2);
            cout<<"Image saved as:"<<img2 <<"\n";
        }
    } else {
        cout << "Enter valid choice!!";
    }
}

// Function to apply lighter purple filter
void applyLighterPurpleFilter(Image& image, const string& filename) {
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Decrease the red and green channels less
            image(i, j, 0) /= 1.5; // Red
            image(i, j, 1) /= 2;   // Green
            // Increase the blue channel more
            image(i, j, 2) *= 1;   // Blue
        }
    }
}


void rotateImage(const string& img, int degree) {
    Image image(img);
    Image image2(image.height, image.width);

    if (degree == 90) {
        for(int i = 0; i < image.width; i++) {
            for(int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    unsigned int x;
                    x = image(i, j, k);
                    image(i, j, k) = image2(image2.width - 1 - j, i, k);
                    image2(image2.width - 1 - j, i, k) = x;
                }
            }
        }
        string  img2, choiceSave;
        cout << "Do you want to save the new file? Y/N\n";
        cin >> choiceSave;
        if (choiceSave == "n" || choiceSave == "N") {
            image2.saveImage(img);
            cout<<"Saved as:"<<img;
        } else if (choiceSave == "y" || choiceSave == "Y") {
            cout << "Enter the new image name to store it with its extension: ";
            cin >> img2;
            image2.saveImage(img2);
            cout<<"Image saved as:"<<img2 <<"\n";
        }
    }
    else if (degree == 180) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height/2; j++) {
                for (int k = 0; k < image.channels; k++) {
                    unsigned int x;
                    x = image(i,j,k);
                    image(i,j,k) = image(image.width-1-i,image.height-1-j,k);
                    image(image.width-1-i,image.height-1-j,k) = x;
                }
            }
        }string  img2, choiceSave;
        cout << "Do you want to save the new file? Y/N\n";
        cin >> choiceSave;
        if (choiceSave == "n" || choiceSave == "N") {
            image.saveImage(img);
            cout<<"Saved as:"<<img;

        } else if (choiceSave == "y" || choiceSave == "Y") {
            cout << "Enter the new image name to store it with its extension: ";
            cin >> img2;
            image.saveImage(img2);
            cout<<"Image saved as:"<<img2 <<"\n";
        }
    }
    else if (degree == 270) {
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                for (int k = 0; k < image.channels; k++) {
                    unsigned int x;
                    x = image(i, j, k);
                    image(i, j, k) = image2(j, image2.height - 1 - i, k);
                    image2(j, image2.height - 1 - i, k) = x;
                }
            }
        }string  img2, choiceSave;
        cout << "Do you want to save the new file? Y/N\n";
        cin >> choiceSave;
        if (choiceSave == "n" || choiceSave == "N") {
            image2.saveImage(img);
            cout<<"Saved as:"<<img;

        } else if (choiceSave == "y" || choiceSave == "Y") {
            cout << "Enter the new image name to store it with its extension: ";
            cin >> img2;
            image2.saveImage(img2);
            cout<<"Image saved as:"<<img2 <<"\n";
        }
    }
    else {
        cout << "Invalid degree. Please enter 90, 180, or 270." << endl;
        return;
    }
}


//Function to crop images
void crop(Image &image, int x, int y, int width, int height) {
// Check the validation of dimensions
    if (x < 0 || y < 0 || width <= 0 || height <= 0 || x + width > image.width || y + height > image.height) {
        cout << "Invalid crop dimensions." << endl;
        return;
    }

// Create a new Image object with the specified width and height
    Image newImg(width, height);

// Copy the pixel data from the original image to the new image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            for (int k = 0; k < image.channels; ++k) {
// Copy pixels from the original image to the new image with correct offsets
                newImg.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
            }
        }
    }

// Assign the cropped image data back to the original image object
    image = newImg;
}



void Infrared(Image& image) {

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            image(i, j, 0) = min(image(i, j, 0) + 200, 255);
            image(i, j, 1) = min(image(i, j, 1) + 50, 255);
            image(i, j, 2) = min(image(i, j, 2) + 50, 255);
        }
    }
}
void resize(Image& img1, int NH, int NW) {
    Image imageNew(NW, NH); // Create a new image with the desired dimensions

    // Calculate the scaling factors
    double scaleX = static_cast<double>(img1.width) / NW;
    double scaleY = static_cast<double>(img1.height) / NH;

    for (int i = 0; i < NW; ++i) {
        for (int j = 0; j < NH; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Calculate the coordinates in the original image
                int ogX = static_cast<int>(i * scaleX);
                int ogY = static_cast<int>(j * scaleY);

                // Sample the pixel value from the original image
                imageNew.setPixel(i, j, k, img1.getPixel(ogX, ogY, k));
            }
        }
    }

    // Update img1 with the resized image
    img1 = imageNew;
}

void flip_horizontal(Image &image){
    for(int i = 0; i < image.width/2; i++){
        for(int j = 0; j < image.height; j++){
            for(int k =0; k < 3; k++){
                unsigned char temp = image.getPixel(i,j,k);
                image.setPixel(i,j,k,image.getPixel(image.width-1-i,j,k));
                image.setPixel(image.width-1-i,j,k,temp);
            }
        }
    }
}

void flip_vertical(Image &image){
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height /2; j++){
            for(int k = 0; k <3; k++){
                unsigned char temp = image(i,j,k);
                image(i,j,k) = image(i,image.height -1-j,k);
                image(i,image.height -1-j,k) = temp;
            }
        }
    }
}

void Merge(Image& image1, Image& image2) {
    // Determine the dimensions for the merged image
    int mergedWidth = min(image1.width, image2.width);
    int mergedHeight = min(image1.height, image2.height);

    // Resize both images to the merged dimensions
    resize(image1, mergedHeight, mergedWidth);
    resize(image2, mergedHeight, mergedWidth);

    // Merge the images pixel by pixel
    for (int i = 0; i < mergedWidth; ++i) {
        for (int j = 0; j < mergedHeight; ++j) {
            for (int k = 0; k < 3; ++k) {
                // Calculate the average pixel value for merging
                int s1 = image1.getPixel(i, j, k);
                int s2 = image2.getPixel(i, j, k);
                int s = (s1 + s2) / 2;

                // Set the pixel in the merged image
                image1.setPixel(i, j, k, s);
            }
        }
    }
}


void sunlightFilter (Image& x ){

    for (int i = 0; i < x.width; ++i) {
        for (int j = 0; j < x.height; ++j) {
            x(i, j, 0) = min(x(i, j, 0) + 50, 255); // Red
            x(i, j, 1) = min(x(i, j, 1) + 30, 255); // Green
            x(i, j, 2) = max(x(i, j, 2) - 20, 0); // Blue
        }
    }
}

void EdgeDetection( Image& x) {
    int sobelKernelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelKernelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    Image y(x.width, x.height); // Create a new image for the result

    for (int i = 1; i < x.width - 1; ++i) {
        for (int j = 1; j < x.height - 1; ++j) {
            for (int k = 0; k < 3; ++k) {
                int Gx = 0, Gy = 0;
                // Apply the Sobel kernels to calculate gradients
                for (int u = -1; u <= 1; ++u) {
                    for (int v = -1; v <= 1; ++v) {
                        Gx += x(i + u, j + v, k) * sobelKernelX[u + 1][v + 1];
                        Gy += x(i + u, j + v, k) * sobelKernelY[u + 1][v + 1];
                    }
                }
                // Calculate the magnitude of the gradient
                int magnitude = sqrt(Gx * Gx + Gy * Gy);
                // Threshold the magnitude to obtain binary edge map
                y(i, j, k) = (magnitude > 128) ? 0 : 255;
            }
        }
    }
    x=y;
}