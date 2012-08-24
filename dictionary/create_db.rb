require 'rubygems'
require 'sqlite3'



    
$db = SQLite3::Database.new "dictionary.db"
puts $db.get_first_value 'SELECT SQLITE_VERSION()'



    



def createScheme()
    
    schema = "create table words ( word varchar(255)  primary key)"
    
    $db.execute schema
end


createScheme()

file = File.new("data/word_list_moby_crossword.flat.txt", "r")
counter = 0
while (line = file.gets)
  
    line = line.gsub( /\r\n/m, "\n" ).strip
  
    puts "#{counter}: #{line}\n"
    counter = counter + 1
    
    stm = $db.prepare "insert into words values(?) "
    stm.bind_param 1, line
    rs = stm.execute
    stm.close
end
file.close


$db.close if $db
