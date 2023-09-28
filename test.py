

#   This is to practice using classes as decorator functions and also
#   previously defining functions nested in another function as a decorator

 class decoratorClass(object):

     def __init__(self, somefunc):
         self.somefunc = somefunc

     def __call__(self, *args, **kwargs):
         print(f"class wrapper executed before {self.somefunc.__name__}")
         return self.somefunc(*args, **kwargs)

 @decoratorClass
 def whatever(name, age, bicboy):
     print(f"display function ran with arguments ({name}) and ({age}) and list of dicts {bicboy}")

 list = [
     {"cream": "sum yung gai"},
     {"meatballs": "wong hong lo"}
     ]

 whatever("john", 25, list)


  def incrementer(number, incrementBy, times):
      print(number)
      sum = number + incrementBy
      for i in range(times):
          print(sum)
          sum = sum + incrementBy
      return incrementer

  incrementer(4, 10, 5)





  def html_tag(tag, msg):
      print("<{0}>{1}</{0}>".format(tag, msg))
      return html_tag

  html_tag('b', 'bolded!')




   from cs50 import get_string

  before = get_string("Before:  ")
  print("After:  ", end="")
  for c in before:
      print(c.upper(), end="")
  print()
