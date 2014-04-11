function map(data)
	for i in string.gmatch(data, "%S+") do -- split by space
	  emit(string.lower(i:gsub('%W','')), 1) -- lowercase and remove punctuation
	end
 end