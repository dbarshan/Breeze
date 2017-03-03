# BREEZE 
> A tool to convert PDF books to kindle format readable books

This is an ongoing hobby project of mine.  I felt difficulties reading pdfs in my kindle. I looked for a software that can convert the pdf to kindle format book exactly without errors/garbage characters. Then I started writing such a tool in C++.

### Steps:
* Open the pdf file and convert each page to image file. 
Status: This is complete. I used poppler library to do this.

* Detect text on the image
Status : This is complete. I used OpenCv to find contours and bounding rectangle around each character.
![N|Solid](https://cloud.githubusercontent.com/assets/25990759/23569758/092701fe-0087-11e7-9c80-dd803d1cac2b.png)

* Categorize the text into sub parts, e.g. which is chapter title, which is heading, which is content, which is page number, which is footer
Status : Pending. Machine learning can be applied or a set of rules.

* Recognize the characters
Status: Pending. Machine learning to be applied. OpenCV's SVM.

* Create a meta file : this will store the different categories of a page, e.g. Title, Heading, Content etc. This will hold the recognized characters alongwith each category.
Status: Pending. This can be simple text file or json file.

* Create HTML file from the meta file.
Status: Pending. Mark up tags to be applied on the meta content

* Use amazon kindlegen program to convert HTML to mobi format




