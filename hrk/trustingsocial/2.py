import sys
import re
import unittest
class Unittest(unittest.TestCase):
  def __init__(self):
    super(unittest.TestCase, self).__init__()
    


def filterOutSomeCharactersInWord(word):
  newWord = word.replace('-', '')
  if len(word) == 1:
    return word
  if re.match('[^a-zA-Z0-9]', word[0]):
    newWord = newWord[1:]
  if re.match('[^a-zA-Z0-9]', word[-1]):
    newWord = newWord[:-1]
  return newWord

def isValidPhoneNumber(phone, prefixes):
  for prefix in prefixes:
    if phone.find(prefix) != -1 and (len(phone) == 11 or len(phone) == 10):
      return True
  return False

def solution(string):
  prefixes = ['0120', '0121', '0122', '0123', '0124', '0125', '0126', '0127',
            '0128', '0129', '0162', '0163', '0164', '0165', '0166', '0167',
            '0168', '0169', '0186', '0188', '0199', '086', '088', '089', '090',
            '091', '092', '093', '094', '095', '096', '097', '098', '099']
  words = string.split(' ')
  phones = []

  i = 0
  while i < len(words):
    word = filterOutSomeCharactersInWord(words[i])
    if not re.search('[^0-9]+', word):
      phone = ''
      for j in xrange(i, len(words)):
        temp = filterOutSomeCharactersInWord(words[j])
        if re.search('[^0-9]+', temp): break
        phone += temp
        if isValidPhoneNumber(phone, prefixes):
          phones.append(phone)
          break
      if j == i: j += 1
      i = j
    else:
      i += 1

  print phones
  return phones

unitTest = Unittest()
unitTest.assertItemsEqual(['0987654321'], solution('0987654321'))
unitTest.assertItemsEqual(['0915528740'], solution('SDT cua toi la     0915528740'))
unitTest.assertItemsEqual(['0910123870'], solution('SDT cua toi la 091 0123 870 40 Nguyen Thi Minh Khai Q1'))
unitTest.assertItemsEqual(['0915528740'], solution('SDT cua toi la 0915528740, xin cam on'))
unitTest.assertItemsEqual(['0987654321'], solution('SDT: 09-87-65-43-21'))
unitTest.assertItemsEqual(['0988000002', '0987000001'], solution('Toi dung 2 so, lan luot la cac so sau : 0987000001 va 0988000002'))
unitTest.assertItemsEqual(['0988000002', '0987000001'], solution('Toi dung 2 so, lan luot la cac so sau :0987000001, va 0988000002'))
unitTest.assertItemsEqual(['0987000001', '0988000002'], solution('0987000001 0988000002'))
unitTest.assertItemsEqual(['0987000001', '0988000002'], solution('098-700-0001 098-800-0002'))
unitTest.assertItemsEqual(['0987000001', '0988000002'], solution('0987-0000-01 0988-00-0002'))



