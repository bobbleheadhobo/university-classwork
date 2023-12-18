# Name: Joey Troyer
# Date: 10/20/22
# input: file "ConvertCSVinput.txt"
# output: write to a file to formatted output from the input file
# problem: Read in a txt with each word seperated by a coma and format it and write it to a different file
# algorithm: Read in file line by line split it by comas and storing it in a 2d array. Each array holds a 
#            sentence and each index holds a word. If person has no middle then i have to swap row[1] and 
#            row[2] and set row[1] to nothing. I write to the file each index in proper format, removing 
#            the ".jpg" and capitalizing each word as needed.

input = "ConvertCSVinput.txt"
output = "Ruby_Output.txt"

#reads in data splits by coma and fills into a 2d array
data = File.readlines(input)[0..-1].map { |line| 
    line.chomp.split(",").map(&:to_s)
}

#checks for no middle name
#if none move row[1] to row[2] and make row[1] empty
for item in data
    if(!item[2])
        item[2] = item[1]
        item[1] = ''
    end
end

# write to file
File.open(output, "w") { |f|
    for item in data
        #checks if theres a middle name
        if(item[1] != '') 
            f.write("#{item[0]},#{item[1]},#{item[2]} ; #{item[0].capitalize()} ; #{item[1].capitalize()} ; #{item[2].chomp(".jpg").capitalize()} ;\n")
        else
            f.write("#{item[0]},#{item[2]} ; #{item[0].capitalize()} ; #{item[2].chomp(".jpg").capitalize()} ;\n")
        end
    end
}
