from watch import parse

def test_parse():
    html1 = '<iframe src="http://www.youtube.com/embed/xvFZjo5PgG0"></iframe>'
    html2 = '<iframe width="560" height="315" src="https://www.youtube.com/embed/xvFZjo5PgG0" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>'
    html3 = '<iframe width="560" height="315" src="https://cs50.harvard.edu/python"></iframe>'
    assert(parse(html1) == "https://youtu.be/xvFZjo5PgG0")
    assert(parse(html2) == "https://youtu.be/xvFZjo5PgG0")
    assert(parse(html3) == None)