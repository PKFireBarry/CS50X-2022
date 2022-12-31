# News Aggregation App
#### Video Demo:  <https://youtu.be/kXU_3xv5Is8>
#### Description:  A news aggregation platform that allows users to browse and search for articles from multiple sources(powered by NewsAPI). My goal is to make it easy for users to stay up-to-date with the latest news and information from a wide range of sources. My Web app is designed to be user-friendly and easy to navigate, with a clean and modern interface that allows users to quickly find the articles they are interested in on mobile or desktop effectively. Here are the latest news headlines for today from United States media companies for the current day. Click on the links in the list to read the full article. Articles update once a day at midnight! Heres how it works! The program an API to collect news from a wide range of sources, including major news outlets, blogs, and social media platforms. The collected news articles are stored in a database or file system for later use. When a user visits the web application, the program retrieves the news articles from the database or file system and displays them on the homepage. The program uses a template engine (such as Jinja2) to render the homepage.html template, which contains the layout and design of the homepage. The homepage.html template includes a list of news articles, each with a title, summary, and link to the full article.  When a user clicks on a link to an article, the program retrieves the full article from the database or file system and displays it to the user. The program uses a template engine (such as Jinja2) to render the article.html template, which contains the layout and design of the article page. The article.html template includes the full text of the article, as well as any associated images or media.

## Features

- Wide range of sources: an  API to collect news from major news outlets, blogs, and social media platforms.
- Clean and modern interface: Our platform has a clean and modern interface that is easy to navigate.


## Getting Started

To get started install the dependencies:
- pip/pip3 install requests
- pip/pip3 install Flask
- pip/pip3 install datetime

Then, run the development server:
export FLASK_APP=app
export FLASK_ENV=development
flask run


## Deployment

To deploy the application, follow these steps:

1. Set the `FLASK_APP` and `FLASK_ENV` environment variables as described above.
2. Use the `flask deploy` command to deploy the application.


## Contributing

We welcome contributions to our news aggregation platform! If you'd like to contribute, please follow these guidelines:

- Fork the repository and create a new branch for your changes.
- Make your changes, and write tests to ensure that they are working as expected.



















