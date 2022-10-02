const path = require("path");
const React = require("react");
const ReactDOMServer = require("react-dom/server");
const express = require("express");

var PageWelcome = require("./PageWelcome.js");

function Shared() {
  return React.createElement(PageWelcome.make, {});
}

const PORT = 5555;
const app = express();

let page = () =>
  React.createElement(
    "html",
    null,
    React.createElement(
      "head",
      null,
      " ",
      React.createElement("title", null, " ", "SSR React", " "),
      " "
    ),
    React.createElement(
      "body",
      null,
      React.createElement(
        "div",
        {
          id: "root",
        },
        React.createElement(Shared, null)
      ),
      React.createElement("script", {
        src: "/static/client.js",
      })
    )
  );

app.get("/", (_req, res) => {
  return res.send(
    `<div id="root">${ReactDOMServer.renderToStaticMarkup(
      React.createElement(page, null)
    )}</div>`
  );
});

app.use(
  express.static(path.resolve(__dirname, ".", "dist"), { maxAge: "30d" })
);

app.listen(PORT, () => {
  console.log(`Server is listening on port ${PORT}`);
});
