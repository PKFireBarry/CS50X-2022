import requests
from flask import Flask, render_template
import datetime

#newsapi.org APIKEY=f71eb428a6704dda9f75918fd2dc7126

app = Flask(__name__)

@app.route('/')
def homepage():
    #grab the date and format it
    date = datetime.datetime.now().strftime("%B %d, %Y")

    #grab the top headlines from the newsapi.org API
    response = requests.get('https://newsapi.org/v2/top-headlines?country=us&apiKey=f71eb428a6704dda9f75918fd2dc7126')

    #convert the response to JSON format and grab the articles
    headlines = response.json()['articles']

    #render the homepage template and pass in the headlines and date
    return render_template('homepage.html', headlines=headlines, date=date)


