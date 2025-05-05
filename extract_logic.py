import spacy

# Load spaCy's English model
nlp = spacy.load("en_core_web_sm")

# Optional: Add your own skill keywords (you can improve this list)
skill_keywords = [
    "Python", "Java", "C++", "C", "SQL", "HTML", "CSS", "JavaScript", "React",
    "Node.js", "Machine Learning", "AI", "Data Analysis", "Communication",
    "Teamwork", "Leadership", "Problem-solving", "Linux", "Docker", "Kubernetes"
]

def extract_skills_from_pdf(pdf_path):
    import fitz  # PyMuPDF
    doc = fitz.open(pdf_path)

    text = ""
    for page in doc:
        text += page.get_text()

    doc.close()

    # Process text with spaCy
    nlp_doc = nlp(text)

    found_skills = set()

    # Match words against skill dictionary (can also use more advanced NER here)
    for token in nlp_doc:
        if token.text in skill_keywords:
            found_skills.add(token.text)

    return list(found_skills)
