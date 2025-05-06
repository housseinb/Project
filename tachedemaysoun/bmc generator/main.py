import sys
import ollama

template = """
Generate a Business Model Canvas (BMC) in 20 phrase for the following project:

{context}
"""

# Read input from input.txt
try:
    with open("C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//input.txt", "r") as input_file:
        project_info = input_file.read().strip()
except FileNotFoundError:
    print("Input file not found.")
    sys.exit(1)

# Parse the input string
try:
    project_data = dict(item.split(":") for item in project_info.split("|"))
    project_description = "\n".join(f"{key}: {value}" for key, value in project_data.items())
except ValueError:
    print("Invalid input format.")
    sys.exit(1)

# Format the prompt with project information
formatted_prompt = template.format(context=project_description)

# Get the response from Ollama
try:
    response = ollama.chat(model="llama3", messages=[{"role": "user", "content": formatted_prompt}])
except Exception as e:
    print(f"Error while communicating with the model: {str(e)}")
    sys.exit(1)

# Write output to output.txt
try:
    with open("C://Users//ASUS-PC//Documents//Nova_Up//bmc generator//output.txt", "w") as output_file:
        if hasattr(response, 'message'):
            output_file.write(response.message.content)
        else:
            output_file.write("Response does not contain 'message' key.")
except IOError:
    print("Failed to write to output.txt.")
    sys.exit(1)