function change(amount)
  if math.type(amount) ~= "integer" then
    error("Amount must be an integer")
  end
  if amount < 0 then
    error("Amount cannot be negative")
  end
  local counts, remaining = {}, amount
  for _, denomination in ipairs({25, 10, 5, 1}) do
    counts[denomination] = remaining // denomination
    remaining = remaining % denomination
  end
  return counts
end

-- Write your first then lower case function here

-- Write your powers generator here

-- Write your say function here

-- Write your line count function here

local open = io.open

function meaningful_line_count(path)
    local file = open(path, "r") 
    if not file then 
    error("No such file")
   end
   count = 0
   currentLine = file:read "*l"
   while currentLine ~= nil do
    while string.gsub(currentLine, "%s+", "") == '' or (string.gsub(currentLine, "%s+", "")):sub(1, 1) == "#" do
        currentLine = file:read "*l"
    end
    currentLine = file:read "*l"
    count = count + 1
  end
    
    file:close()
    return count
end



-- Write your Quaternion table here
