//
// Created by floodd on 23/03/2022.
//
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"
#include <iostream>
#include <cmath>

bool Image::load(string filename) {
    ifstream ifs(filename, std::ios::binary);
    string magicNumber;
    ifs >> magicNumber;
    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
    ifs.ignore(256, '\n');
    if (p == 255) {
        delete[] pixels;
        pixels = new Rgb[w * h];
        unsigned char pix[3];
        for (int i = 0; i < w * h; i++) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        return true;
    }
    return false;
}

bool Image::loadRaw(string filename) {

    return false;
}

bool Image::savePPM(string filename) {

    if (this->w == 0 || this->h == 0) {
        return false;
    } else {
        std::ofstream ofs;
        ofs.open(filename, std::ios::binary);
        ofs << "P6\n" << this->w << " " << this->h << "\n255\n";
        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < this->w * this->h; i++) {
            r = static_cast<unsigned char>(std::min(1.f, (float) this->pixels[i].r) * this->pixels[i].r);
            g = static_cast<unsigned char>(std::min(1.f, (float) this->pixels[i].g) * this->pixels[i].g);
            b = static_cast<unsigned char>(std::min(1.f, (float) this->pixels[i].b) * this->pixels[i].b);
            ofs << r << g << b;
        }
        ofs.close();
    }
    return true;
}


void Image::filterRed() {
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}

void Image::filterGreen() {
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}

void Image::filterBlue() {
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}

//http://opencv-tutorials-hub.blogspot.com/2015/12/how-to-convert-color-image-into-grayscaleopencvimage-without-using-CVLOADIMAGEGRAYSCALE-methods-of-converting-RGB-into-greyscale-image-luminosity-method-weighted-average-pixels-channels-of-greyscale-image-opencv-hub-code-examples.html
void Image::greyScale() {
    for (int i = 0; i < w * h; i++) {
        this->pixels[i].r = (this->pixels[i].r + this->pixels[i].g + this->pixels[i].b) / 3;
        this->pixels[i].g = (this->pixels[i].r + this->pixels[i].g + this->pixels[i].b) / 3;
        this->pixels[i].b = (this->pixels[i].r + this->pixels[i].g + this->pixels[i].b) / 3;
    }
}

//https://www.youtube.com/watch?v=6byB1jX3Fnk
void Image::flipHorizontal() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w / 2; j++) {
            swap(pixels[j + i * w], pixels[i * w + (w - j)]);
        }
    }
}

//https://www.youtube.com/watch?v=6byB1jX3Fnk
void Image::flipVertically() {
    for (int i = 0; i < h / 2; i++) {
        for (int j = 0; j < w; j++) {
            swap(pixels[j + i * w], pixels[j + (h - 1 - i) * w]);
        }
    }
}

//https://stackoverflow.com/questions/65144598/c-cuda-invert-image-colors
void Image::invertColor() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            pixels[y * w + x].r = 256 - pixels[y * w + x].r;
            pixels[y * w + x].g = 256 - pixels[y * w + x].g;
            pixels[y * w + x].b = 256 - pixels[y * w + x].b;
        }
    }
}


void Image::turnImageIntoBlack() {
    for (int i = 0; i < w * h; ++i) {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}

void Image::rotate270() {
    Rgb *tempArr = new Rgb[w * h];

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int r = ((x * h) - (h - y - 1));

            tempArr[r] = pixels[y * w + x];
        }
    }
    pixels = tempArr;
    int t = w;
    w = h;
    h = t;
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth() {
    return w;
}

int Image::getHeight() {
    return h;
}

Rgb *Image::getImage() {
    return pixels;
}