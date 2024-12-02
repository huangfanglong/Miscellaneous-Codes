"""
CS50 P-Shirt
After finishing CS50 itself, students on campus at Harvard traditionally receive their very own I took CS50 t-shirt. No need to buy one online, but like to try one on virtually?

In a file called shirt.py, implement a program that expects exactly two command-line arguments:

in sys.argv[1], the name (or path) of a JPEG or PNG to read (i.e., open) as input
in sys.argv[2], the name (or path) of a JPEG or PNG to write (i.e., save) as output
The program should then overlay shirt.png (which has a transparent background) on the input after resizing and cropping the input to be the same size, saving the result as its output.

Open the input with Image.open, per pillow.readthedocs.io/en/stable/reference/Image.html#PIL.Image.open, resize and crop the input with ImageOps.fit, per pillow.readthedocs.io/en/stable/reference/ImageOps.html#PIL.ImageOps.fit, 
using default values for method, bleed, and centering, overlay the shirt with Image.paste, per pillow.readthedocs.io/en/stable/reference/Image.html#PIL.Image.Image.paste, and save the result with Image.save, 
per pillow.readthedocs.io/en/stable/reference/Image.html#PIL.Image.Image.save.

The program should instead exit via sys.exit:

if the user does not specify exactly two command-line arguments,
if the input’s and output’s names do not end in .jpg, .jpeg, or .png, case-insensitively,
if the input’s name does not have the same extension as the output’s name, or
if the specified input does not exist.
Assume that the input will be a photo of someone posing in just the right way, like these demos, so that, when they’re resized and cropped, the shirt appears to fit perfectly.

If you’d like to run your program on a photo of yourself, first drag the photo over to VS Code’s file explorer, into the same folder as shirt.py. No need to submit any photos with your code. 
But, if you would like, you’re welcome (but not expected) to share a photo of yourself wearing your virtual shirt in any of CS50’s communities!
"""

from PIL import Image, ImageOps, UnidentifiedImageError
import sys
import os

def main():
    if len(sys.argv) > 3:
        sys.exit("Too many command-line arguments")
    elif len(sys.argv) < 3:
        sys.exit("Too few command-line arguments")

    if is_file_path_a_valid_png_or_jpeg_file(sys.argv[1]) is False:
        sys.exit("Invalid input")
    elif  is_file_path_a_valid_png_or_jpeg_file(sys.argv[2]) is False:
        sys.exit("Invalid output")
    elif does_format_of_input_output_match(sys.argv[1], sys.argv[2]) is False:
        sys.exit("Input and output have different extensions")

    input_image  = sys.argv[1]
    output_image = sys.argv[2]

    try:
        with Image.open(input_image) as input_img:
            with Image.open("shirt.png") as shirt_img:
                shirt_img_size = shirt_img.size
                # Resize the input img to fit the shirt.png image
                input_img = ImageOps.fit(input_img, shirt_img_size)
                # Paste shirt img onto input img. Since shirt.png is transparent, by passing it again to the optional mask param its alpha channel will be used as the mask therefore keeping transparency of shirt.png
                input_img.paste(shirt_img, mask=shirt_img)
                input_img.save(output_image, quality=100)
        
    except FileNotFoundError:
        sys.exit("FileNotFoundError: Not a valid file/path")
    except UnidentifiedImageError:
        sys.exit("PIL.UnidentifiedImageError: Not a valid image file")

def is_file_path_a_valid_png_or_jpeg_file(file_path):
    if file_path.endswith("png"):
        return True
    elif file_path.endswith("jpg"):
        return True
    elif file_path.endswith("jpeg"):
        return True
    else:
        return False
    
def does_format_of_input_output_match(file_path_1, file_path_2):
    file_extension_1 = os.path.splitext(file_path_1)[1]
    file_extension_2 = os.path.splitext(file_path_2)[1]
    return file_extension_1 == file_extension_2

if __name__ == "__main__":
    main()