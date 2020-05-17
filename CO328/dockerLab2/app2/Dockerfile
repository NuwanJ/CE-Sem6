
FROM node:latest
COPY . ./app
RUN npm install http
ENV message='Hello World !'
ENV colour=red
EXPOSE 3000
CMD ["node", "./app2.js"]
