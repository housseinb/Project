# generate_logo.py
import sys
import os
from datetime import datetime
from diffusers import StableDiffusionPipeline
import torch

def generate_logo(startup, industry, style, icon, color, font, filename=None):
    prompt = f"A {style} logo for a startup called '{startup}' in the {industry} industry"
    if icon: prompt += f", with a {icon}"
    if color: prompt += f", using {color} color"
    if font: prompt += f", using a {font} font"
    prompt += ", minimal flat design, high-resolution vector logo"

    # Load AI model
    pipe = StableDiffusionPipeline.from_pretrained("CompVis/stable-diffusion-v1-4").to("cpu")
    image = pipe(prompt).images[0]

    os.makedirs("generated_logos", exist_ok=True)

    # Use provided filename or generate one
    if not filename:
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        filename = f"{startup}_{timestamp}.png"

    output_path = os.path.join("generated_logos", filename)
    image.save(output_path)

    print(output_path)  # For Qt to read
    return output_path

if __name__ == "__main__":
    if len(sys.argv) == 8:
        startup, industry, style, icon, color, font, filename = sys.argv[1:]
        generate_logo(startup, industry, style, icon, color, font, filename)
    else:
        startup, industry, style, icon, color, font = sys.argv[1:7]
        generate_logo(startup, industry, style, icon, color, font)
