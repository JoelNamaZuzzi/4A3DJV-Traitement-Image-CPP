#pragma warning(disable:4996)

#include "Image.h"
#include <iostream>
#include <sstream>
#include <stdio.h> 
#include <iomanip>
#include <setjmp.h>
#include <filesystem>

std::filesystem::path Image::getSRC() const {
    return this->fsp;
}

void Image::setSRC(std::filesystem::path p) {
    this->fsp = p;
}

ImageInfo& Image::getImages() const
{
    return *images;
}

void Image::setImages(ImageInfo* images) {
    this->images = images;
}

int Image::getNBImages() const {
    return this->nbImages;
}
void Image::setNBImages(int nbImgs) {
    this->nbImages = nbImgs;
}

int convertColor(int color) {

    //permet de transformer la valeur en entré en réel int, car la couleur du pixel récup est en hex donc pour le traitement et les manips cest pas ouf
    std::stringstream ss;
    unsigned int valhex;
    ss << std::hex << (int)color;
    ss >> valhex;
    return valhex;
}

void triBulle(int* tab, int n)
{
    //pour trier le tableau en entrée
    bool stop;
    int tmp, j = 0;
    do
    {
        stop = true;
            for (int i = n - 1; i > j; --i)
            {
                if (tab[i] < tab[i - 1]) //l element le plus petit remonte vers le debut
                {
                    tmp = tab[i];
                    tab[i] = tab[i - 1];
                    tab[i - 1] = tmp;
                    stop = false;
                }
            }
        j++;
    } while (!stop);//si pas de changement à un passage -> tab trie
}

unsigned char* raw_image = NULL;


int widthImg;
int heightImg;
int nbImages;

ImageInfo Image::readImg() {
    raw_image = NULL;


    //autre manière d'ouvrir un fichier

    //cinfo.err = jpeg_std_error(jerr);

    //FILE* fp;
    //errno_t err;


    /*if ((err = fopen_s(&fp, "C:/Users/kidom/OneDrive/Bureau/3djv/c++/Images/bantha.png", "rb")) != 0) {
        printf("Error: failed to open %s\n", "C:/Users/kidom/OneDrive/Bureau/3djv/c++/Images/bantha.png");
        return false;
    }
    else {
        printf("no error\n");
    }*/


    ImageInfo newImage;
    std::filesystem::path p = this->fsp;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];

    FILE* fp;
    unsigned long location = 0;
    int i = 0;
    //ouverture du fichier
    if ((fp = fopen(p.string().c_str(), "rb")) == NULL) {
        printf("Error: failed to open %s\n", src);
        exit(1);
    }
    else {
        printf("no error");
    }

    //commencement de la lecture du fichier
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fp);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);
    //printf("\ncomponents = %d\n", cinfo.num_components);

    raw_image = (unsigned char*)malloc(cinfo.output_width * cinfo.output_height * cinfo.num_components);
    row_pointer[0] = (unsigned char*)malloc(cinfo.output_width * cinfo.num_components);

    //lecture
    while (cinfo.output_scanline < cinfo.image_height)
    {
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
        for (i = 0; i < cinfo.image_width * cinfo.num_components; i++)
            raw_image[location++] = row_pointer[0][i];
    }

    //donnée à retourner pour être ajouter à notre tableau d'images
    newImage.width = cinfo.image_width;
    newImage.height = cinfo.image_height;
    newImage.ch = cinfo.output_components;
    newImage.data = new uint8_t[newImage.width * newImage.height * newImage.ch];

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    free(row_pointer[0]);

    fclose(fp);

    newImage.path = p;
    //writeImg(newImage, newpath.c_str());

    return newImage;
}

int Image::cop(ImageInfo image)
{
    //cop permet de créer une image de la meme taille que celle passé en paramètre en blanc
    int width = image.width;
    int height = image.height;
    int bytes_per_pixel = 3;   /* or 1 for GRACYSCALE images */
    int color_space = JCS_RGB;

    const char* copy = "../Image/Vide.png";

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    FILE* outfile;
    //wb pour écrire ou création d'un nouveau fichier en binaire
    if ((outfile = fopen(copy, "wb")) == NULL) {
        printf("Error: failed to open %s\n", copy);
        return -1;
    }
    else {
        printf("no error");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = bytes_per_pixel;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);

    jpeg_start_compress(&cinfo, TRUE);

    //changement des pixels de couleur
    for (int i = 0; i < cinfo.image_height; i++) {
        for (int j = 0; j < cinfo.image_width; j++) {
            // Pixel (i,j)
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0] = 255; // Red Pixel
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1] = 255; // Green Pixel
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2] = 255;// Blue Pixel
        }
    }

    while (cinfo.next_scanline < cinfo.image_height)
    {

        row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);

    return 1;
}

int Image::getBackground()
{
    //récupération du background des images

    const char* dstc = "../Image/Background.png";//non de l'image à créer ou modifier
    int nb_images = this->nbImages;
    Image* imgs = new Image[nb_images];

    /*for (int i = 0; i < this->nbImages; i++) {
        std::cout << this->nbImages << " " << images[i].path.string().c_str() << " a" << std::endl;
    }*/
    
    int width = images[0].width;
    int height = images[0].height;
    int bytes_per_pixel = 3;
    int color_space = JCS_RGB;

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    JSAMPROW row_pointer[1];
    FILE* outfile;
    if ((outfile = fopen(dstc, "wb")) == NULL) {
        printf("Error: failed to open %s\n", dstc);
        return -1;
    }
    else {
        printf("no error");
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = bytes_per_pixel;
    cinfo.in_color_space = JCS_RGB;
    
    jpeg_set_defaults(&cinfo);

    jpeg_start_compress(&cinfo, TRUE);


    int red;
    int green;
    int blue;
    //tableaux où seront stockés les couleurs des différents pixels des images car sinon le programmes si on load et récup à chaque pixel par pixel
    int** r_tab = new int* [nb_images];
    for (int i = 0; i < nb_images; i++) {

        r_tab[i] = new int[images[0].height * images[0].width];

    }

    int** g_tab = new int* [nb_images];
    for (int j = 0; j < nb_images; j++) {

        g_tab[j] = new int[images[0].height * images[0].width];

    }

    int** b_tab = new int* [nb_images];
    for (int k = 0; k < nb_images; k++) {

        b_tab[k] = new int[images[0].height * images[0].width];

    }

    //récupétation des pixels des images
    for (int k = 0; k < nb_images; k++) {
        imgs[0] = Image(images[k].path);
        imgs[0].readImg();
        int counter = 0;

        for (int i = 0; i < cinfo.image_height; i++) {
            for (int j = 0; j < cinfo.image_width; j++) {
                
                // Pixel (i,j)


                red = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0]);
                green = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1]);
                blue = convertColor((int)raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2]);

                r_tab[k][counter] = red;
                g_tab[k][counter] = green;
                b_tab[k][counter] = blue;

                counter++;


                //std::cout << counter << std::endl;
                //std::cout << "red :" << red << " green: " << green << " blue : " << blue << " " << std::endl;
            }
        }
    }

    // algo pour avoir les médians du pixel des images
    int counter = 0;
    for (int i = 0; i < cinfo.image_height; i++) {
        for (int j = 0; j < cinfo.image_width; j++) {
            int* r_med = new int[nb_images];
            int* g_med = new int[nb_images];
            int* b_med = new int[nb_images];

            for (int k = 0; k < nb_images; k++) {

                r_med[k] = r_tab[k][counter];
                g_med[k] = g_tab[k][counter];
                b_med[k] = b_tab[k][counter];

            }

            triBulle(r_med, nb_images);
            triBulle(g_med, nb_images);
            triBulle(b_med, nb_images);

            red = r_med[(int)nb_images / 2];
            green = g_med[(int)nb_images / 2];
            blue = b_med[(int)nb_images / 2];

            //changement de la couleur du pixel avec la valeur médiane
            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 0] = red; // Red Pixel

            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 1] = green; // Green Pixel

            raw_image[(i * cinfo.image_width * 3) + (j * 3) + 2] = blue; // Blue Pixel

            counter++;
        }
    }


    while (cinfo.next_scanline < cinfo.image_height)
    {
        row_pointer[0] = &raw_image[cinfo.next_scanline * cinfo.image_width * cinfo.input_components];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);

    cop(images[0]);
    return 1;
}