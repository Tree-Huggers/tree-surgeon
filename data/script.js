
function Expand() {
  var button = document.getElementById("expandBtn");
  var dots = document.getElementById("dots");
  var fullParagraph = document.getElementById("read_more");

  if (dots.style.display === "none") {
    dots.style.display = "inline";
    button.innerHTML = "Read more";
    fullParagraph.style.display = "none";
  }
  else {
    dots.style.display = "none";
    button.innerHTML = "Read less";
    fullParagraph.style.display = "inline";
  }
} 