
# remove duplicate items in list
# and reserve the last duplicate item
def rm_dup(seq):   
  # order preserving
  checked = []
  seq.reverse()
  for e in seq:
    if e not in checked:
        checked.append(e)
  checked.reverse()
  return checked

