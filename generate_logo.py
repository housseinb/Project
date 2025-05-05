# generate_logo.py
import sys
import os
from datetime import datetime
from diffusers import StableDiffusionPipeline
import torch
torch.set_num_threads(4)  # Adjust this based on your CPU


def generate_logo(startup, industry, style, icon, color, font, filename=None):
    prompt = f"A {style} logo for a startup called '{startup}' in the {industry} industry, featuring the word '{startup}' clearly in the logo, with a {icon} icon, using {color} colors and {font} typography, minimal flat design, high-resolution vector style"
    if icon: prompt += f", with a {icon}"
    if color: prompt += f", using {color} color"
    if font: prompt += f", using a {font} font"
    prompt += ", minimal flat design, high-resolution vector logo"

    # Load AI model
    if torch.cuda.is_available():
        pipe = StableDiffusionPipeline.from_pretrained("CompVis/stable-diffusion-v1-4", torch_dtype=torch.float16)
        pipe = pipe.to("cuda")
    else:
        pipe = StableDiffusionPipeline.from_pretrained("CompVis/stable-diffusion-v1-4")
        pipe = pipe.to("cpu")

    image = pipe(prompt).images[0]

    os.makedirs("generated_logos", exist_ok=True)

    # Use provided filename or generate one
    if not filename:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"{startup}_{timestamp}.png"
        output_path = os.path.join("generated_logos", filename)
    else:
        output_path = filename  # full path already passed from Qt

    image.save(output_path)

    print(output_path)
    return output_path

if __name__ == "__main__":
    if len(sys.argv) == 8:
        startup, industry, style, icon, color, font, filename = sys.argv[1:]
        output_path = generate_logo(startup, industry, style, icon, color, font, filename)
    else:
        startup, industry, style, icon, color, font = sys.argv[1:]
        output_path = generate_logo(startup, industry, style, icon, color, font)
