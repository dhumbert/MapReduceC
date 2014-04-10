function map(data)
	for i in string.gmatch(data, "%S+") do -- split by space
	  return {string.lower(i:gsub('%W','')), 1} -- lowercase and remove punctuation
	  -- todo can't return. need to inject an emit function or something.
	end
 end