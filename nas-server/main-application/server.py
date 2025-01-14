from flask import Flask, request, jsonify
import os

app = Flask(__name__)

# Define the upload folder
UPLOAD_FOLDER = 'C://VSCode//RFTA//nas-server//main-application//test'
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Ensure the upload folder exists
if not os.path.exists(UPLOAD_FOLDER):
    os.makedirs(UPLOAD_FOLDER)

@app.route('/upload', methods=['POST'])
def upload_file():
    # Check if a file is included in the request
    if 'file' not in request.files:
        return jsonify({"error": "No file part in the request"}), 400

    file = request.files['file']

    # Check if the file has a name
    if file.filename == '':
        return jsonify({"error": "No selected file"}), 400

    # Save the file to the upload folder
    file_path = os.path.join(app.config['UPLOAD_FOLDER'], file.filename)
    file.save(file_path)

    print(f"Uploading file: {file.filename} to {file_path}")
    return jsonify({"message": "File uploaded successfully", "file_path": file_path}), 200

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)  # Use SSL for HTTPS