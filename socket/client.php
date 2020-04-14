<?php
/**
 * Usage:
 *  php client.php msg
 */
if ($argc != 2) {
    die("Usage: php client.php msg\n");
}

$conn = stream_socket_client('tcp://127.0.0.1:12345', $errno, $errstr, 30);
if (!$conn) {
    die("connect error: $errstr($errno)");
}

fwrite($conn, $argv[1]);

$response = fread($conn, 100);
echo "Response from server: " . $response . "\n";
