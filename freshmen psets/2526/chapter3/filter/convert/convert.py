import os
import pathlib
import sys
from PIL import Image

OUTPUT_DIR = "bmp_output"
SUPPORTED_FORMAT = ['.jpg', '.JPG', '.JPEG', '.jpeg', '.png', '.PNG']

def main():

    # Sanity checks
    if len(sys.argv) != 2:
        sys.exit("Usage: python3 convert.py INPUT_DIR")

    input_dir = sys.argv[1]
    if not os.path.isdir(input_dir):
        sys.exit("Invalid input directory")

    # Create output folder if not existed already
    if not os.path.isdir(OUTPUT_DIR):
        os.mkdir(OUTPUT_DIR)

    for file in os.listdir(input_dir):
        try:

            # Skip unsupported files
            file_ext = pathlib.Path(file).suffix
            if file_ext not in SUPPORTED_FORMAT:
                continue

            # Read an image
            img = Image.open(f'{input_dir}/{file}')

            # Strip alpha channel for a png image
            if file_ext == '.png' or file_ext == '.PNG':
                img = Image.merge("RGB", (img.split()[:3]))

            # Save image as a bitmap file
            img.save(f"{OUTPUT_DIR}/{file.replace(file_ext, '.bmp')}")
        except Exception as e:
            print(f'Errored converting {file} to bitmap file')
            print(e)

    print(f"New bitmap file(s) created in {OUTPUT_DIR} folder")

if __name__ == "__main__":
    main()
