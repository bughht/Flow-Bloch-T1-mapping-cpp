import os
from ipynbcompress import compress

path="python"
ipypath= [os.path.join(path,f) for f in os.listdir(path) if (not os.path.isdir(os.path.join(path, f)) and f.endswith(".ipynb"))]
print(ipypath)

for filename in ipypath:
    # outfilename=os.path.splitext(filename)[0]+"_compressed.ipynb"
    compress(filename, output_filename=filename, img_width=800, img_format='jpeg')
