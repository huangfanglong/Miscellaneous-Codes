<?php
    function draw_table($rows)
    {
        if (count($rows) > 0)
        {
            echo "<table border=1 cellspacing=1>";
            echo "<tr>";           

            foreach ($rows[0] as $key => $item)
            {
                echo "<th>$key</th>";
            }
            echo "</tr>";
            
            foreach ($rows as $row)
            {
                echo "<tr>";

                foreach ($row as $key => $item)
                {
                    echo "<td>$item</td>";
                }
                echo "</tr>";
            }
            echo "</table>";
        }
        else
        {
            echo "TABLE IS EMPTY!";
        }
    }
?>
