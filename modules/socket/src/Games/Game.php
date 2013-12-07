<?php
namespace Games;
use Ratchet\MessageComponentInterface;
use Ratchet\ConnectionInterface;

define('DRUPAL_ROOT', '/home/drupalpro/websites/dgms.dev/');
$_SERVER['REMOTE_ADDR'] = '127.0.0.1';

chdir(DRUPAL_ROOT);
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);


class Game implements MessageComponentInterface {
    protected $clients;
    protected $games;

    public function __construct() {
        $this->clients = new \SplObjectStorage;
    }

    public function onOpen(ConnectionInterface $conn) {
        // Store the new connection to send messages to later
        $this->clients->attach($conn);

        echo "New connection! ({$conn->resourceId})\n";
    }
    /**
    * When client send Message to server
    * Proccess the action and return messages back to users.
    * Example : conn.send('[{"command":"trigger","hook":"game_join","game":{"session":"a9db5e8fd7bff90d926e5b7c7ac49bae"},"params":{"player_name":"avinoam"}}]')
    **/
    public function onMessage(ConnectionInterface $from, $msg) {
        $actions = drupal_json_decode($msg);
        if(empty($actions) || !is_array($actions)) {
            $re = array('Error'=>'action is empty');
            $from->send(drupal_json_encode($re));
        }
        print_r($actions);
       try {
            foreach($actions as $action) {
                $re = $this->_proccess_action($action);
            } 
        } catch(Exception $e) {
            echo $e->getMessage();
            $from->send(array('Error'=>'server error'));
        }
        $from->send(drupal_json_encode($re));
        
        foreach ($this->clients as $client) {
            if ($from !== $client) {// The sender is not the receiver, send to each client connected
                $client->send($re);
            }
        }
    }
    private function _proccess_action($action) {
            global $user;

          switch ($action['command']) {
            case "trigger":
                if(!isset($action['game']) || !isset($action['game']['session'])) {
                    return array("Error"=>'game not found');
                }
                if(!isset($action['hook'])) {
                    return array("Error"=>'Hook not found');
                }
                $running_game = reset(entity_load("running_game",FALSE,array('session'=>$action['game']['session'])));
                $game = game_load($running_game->gid);

                $_SESSION['game_response'] = array();

                // Always add game instance to rules_invoke_event
                $action['params']['running_game'] = $running_game;
                $action['params']['game'] = $game;
                $response = rules_invoke_event_by_args($action['hook'], $action['params']);
                $game_response = $_SESSION['game_response'];
                unset($_SESSION['game_response']);
                if (empty($game_response)) {
                  $response = array();
                }
                if (empty($game_response)) {
                  $response;
                }
                  
                $response = drupal_json_encode($game_response);
                return $response;

            break;
            default:
                echo "Action not recognize";
                return array('Error'=>"Action not recognize");
                //throw new Exception('Action not recognize.');
            break;
        }


    }
    public function onClose(ConnectionInterface $conn) {
        // The connection is closed, remove it, as we can no longer send it messages
        $this->clients->detach($conn);

        echo "Connection {$conn->resourceId} has disconnected\n";
    }

    public function onError(ConnectionInterface $conn, \Exception $e) {
        echo "An error has occurred: {$e->getMessage()}\n";

        $conn->close();
    }
}