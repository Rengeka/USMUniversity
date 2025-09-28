
let str1 = 'hi_there';
let str2 = 'hello-world';

str1 = toCamelCase(str1);
str2 = toCamelCase(str2);

str4 = "Buckethead";
str5 = "DeathCubeK";

console.log(areAnagrams(str4, str5));

console.log(str1);
console.log(str2);


function toCamelCase(str)
{
    let string = "";
    let nextToUpperCase = false;

    for(let i = 0; i < str.length; i++)
    {
        
        if(str[i] != "-" && str[i] != "_")
        {
            if(nextToUpperCase)
            {
                string += str[i].toUpperCase();
                nextToUpperCase = false;
            } 
            else
            {
                string += str[i];
            }
        }
        else
        {
            nextToUpperCase = true;
        }
    }

    return string;
}

function areAnagrams(str1, str2)
{
    if(str1.length == str2.length)
    {
        let isFalse = true;

        for(let i = 0; i < str1.length; i++)
        {
            for(let j = 0; j < str2.length; j++)
            {
                if(str1[i] == str2[j] || str1[i] == str2[j].toUpperCase() || str1[i].toUpperCase() == str2[j])
                {
                  
                    str2 = str2.slice(0, j) + str2.slice(j + 1, str2.length);
                    isFalse = false;

                    break;
                }
        
            }

            if(isFalse == true)
            {
                return false;
            }

            isFalse = true;
        }
    }
    else
    {
        return false;
    }

    return true;
}