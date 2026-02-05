local some_extra_things = {
  thank = {
    him = "Joe",
    her = "Mary",
    none = nil
  },
  you = {
     { what = "hey" },
     { how = "hey" },
     { why = "hey" },
  },
  very = {
    numbers = {
      1,
      2,
      3,
    }
  },
  much = {
    [[123456]],
    [[24681012]],
    [[999999999999]],
  },
}

print(some_extra_things.thank.her)
print(some_extra_things)

for _, text in pairs(some_extra_things.you) do
  print(text.how)
  print(text.what)
  print(text.why)
end
